#include <sdbusplus/message.hpp>

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include <gtest/gtest.h>

using namespace std::string_literals;

/* Suite tests that object_path and signature can be cleanly converted to
 * and from strings and used as container parameters.
 */

TEST(MessageNativeTypeConversions, ObjectPath)
{
    std::string s1 = sdbusplus::message::object_path("/asdf/");
    sdbusplus::message::object_path p = std::move(s1);

    ASSERT_EQ("/asdf/", p);
    ASSERT_EQ(p, "/asdf/");
}

TEST(MessageNativeTypeConversions, Signature)
{
    std::string s2 = sdbusplus::message::signature("iii");
    sdbusplus::message::signature sig = s2;

    ASSERT_EQ(sig, s2);
    ASSERT_EQ(s2, sig);
}

TEST(MessageNativeTypeConversions, SignatureInVector)
{
    std::vector<sdbusplus::message::signature> v = {
        sdbusplus::message::signature("iii")};

    ASSERT_EQ(v.front(), "iii");
}

TEST(MessageNativeTypeConversions, SignatureInMap)
{
    std::map<sdbusplus::message::signature, int> m = {
        {sdbusplus::message::signature("iii"), 1}};

    ASSERT_EQ(m[sdbusplus::message::signature("iii")], 1);
}

TEST(MessageNativeTypeConversions, SignatureInUnorderedMap)
{
    std::unordered_map<sdbusplus::message::signature, int> u = {
        {sdbusplus::message::signature("iii"), 2}};

    ASSERT_EQ(u[sdbusplus::message::signature("iii")], 2);
}

TEST(MessageNativeTypeConversions, WrapperReference)
{
    auto orig = "str"s;
    sdbusplus::message::object_path obj = orig;
    auto out = static_cast<std::string>(obj);
    EXPECT_EQ(orig, out);
}

TEST(MessageNativeTypeConversions, WrapperMove)
{
    auto orig = "str"s;
    sdbusplus::message::object_path obj = orig;
    auto out = static_cast<std::string>(std::move(obj));
    EXPECT_EQ(orig, out);
}

#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  TEST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_str_eq (char*,char*) ; 
 int /*<<< orphan*/  TEST_str_ne (char*,char*) ; 

__attribute__((used)) static int test_string(void)
{
    static char buf[] = "abc";

    if (!TEST(1, TEST_str_eq(NULL, NULL))
        | !TEST(1, TEST_str_eq("abc", buf))
        | !TEST(0, TEST_str_eq("abc", NULL))
        | !TEST(0, TEST_str_eq("abc", ""))
        | !TEST(0, TEST_str_eq(NULL, buf))
        | !TEST(0, TEST_str_ne(NULL, NULL))
        | !TEST(0, TEST_str_eq("", NULL))
        | !TEST(0, TEST_str_eq(NULL, ""))
        | !TEST(0, TEST_str_ne("", ""))
        | !TEST(0, TEST_str_eq("\1\2\3\4\5", "\1x\3\6\5"))
        | !TEST(0, TEST_str_ne("abc", buf))
        | !TEST(1, TEST_str_ne("abc", NULL))
        | !TEST(1, TEST_str_ne(NULL, buf))
        | !TEST(0, TEST_str_eq("abcdef", "abcdefghijk")))
        goto err;
    return 1;

err:
    return 0;
}
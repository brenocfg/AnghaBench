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
 int TEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_str_eq (char const*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int test_long_output(void)
{
    const char *p = "1234567890123456789012345678901234567890123456789012";
    const char *q = "1234567890klmnopqrs01234567890EFGHIJKLM0123456789XYZ";
    const char *r = "1234567890123456789012345678901234567890123456789012"
                    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY+"
                    "12345678901234567890123ABC78901234567890123456789012";
    const char *s = "1234567890123456789012345678901234567890123456789012"
                    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY-"
                    "1234567890123456789012345678901234567890123456789012"
                    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    return TEST(0, TEST_str_eq(p,  q))
           & TEST(0, TEST_str_eq(q, r))
           & TEST(0, TEST_str_eq(r, s))
           & TEST(0, TEST_mem_eq(r, strlen(r), s, strlen(s)));
}
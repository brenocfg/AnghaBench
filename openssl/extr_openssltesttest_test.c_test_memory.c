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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  TEST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (char*,int,char*,int) ; 
 int /*<<< orphan*/  TEST_mem_ne (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_memory(void)
{
    static char buf[] = "xyz";

    if (!TEST(1, TEST_mem_eq(NULL, 0, NULL, 0))
        | !TEST(1, TEST_mem_eq(NULL, 1, NULL, 2))
        | !TEST(0, TEST_mem_eq(NULL, 0, "xyz", 3))
        | !TEST(0, TEST_mem_eq(NULL, 7, "abc", 3))
        | !TEST(0, TEST_mem_ne(NULL, 0, NULL, 0))
        | !TEST(0, TEST_mem_eq(NULL, 0, "", 0))
        | !TEST(0, TEST_mem_eq("", 0, NULL, 0))
        | !TEST(0, TEST_mem_ne("", 0, "", 0))
        | !TEST(0, TEST_mem_eq("xyz", 3, NULL, 0))
        | !TEST(0, TEST_mem_eq("xyz", 3, buf, sizeof(buf)))
        | !TEST(1, TEST_mem_eq("xyz", 4, buf, sizeof(buf))))
        goto err;
    return 1;

err:
    return 0;
}
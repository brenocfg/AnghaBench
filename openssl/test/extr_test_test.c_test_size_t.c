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
 int /*<<< orphan*/  TEST_size_t_eq (size_t,size_t) ; 
 int /*<<< orphan*/  TEST_size_t_ge (size_t,size_t) ; 
 int /*<<< orphan*/  TEST_size_t_gt (size_t,size_t) ; 
 int /*<<< orphan*/  TEST_size_t_le (size_t,size_t) ; 
 int /*<<< orphan*/  TEST_size_t_lt (size_t,size_t) ; 
 int /*<<< orphan*/  TEST_size_t_ne (size_t,size_t) ; 

__attribute__((used)) static int test_size_t(void)
{
    if (!TEST(1, TEST_size_t_eq((size_t)10, (size_t)10))
        | !TEST(0, TEST_size_t_eq((size_t)10, (size_t)12))
        | !TEST(1, TEST_size_t_ne((size_t)10, (size_t)12))
        | !TEST(0, TEST_size_t_ne((size_t)24, (size_t)24))
        | !TEST(1, TEST_size_t_lt((size_t)30, (size_t)88))
        | !TEST(0, TEST_size_t_lt((size_t)88, (size_t)30))
        | !TEST(1, TEST_size_t_le((size_t)30, (size_t)88))
        | !TEST(1, TEST_size_t_le((size_t)33, (size_t)33))
        | !TEST(0, TEST_size_t_le((size_t)88, (size_t)30))
        | !TEST(1, TEST_size_t_gt((size_t)52, (size_t)33))
        | !TEST(0, TEST_size_t_gt((size_t)33, (size_t)52))
        | !TEST(1, TEST_size_t_ge((size_t)52, (size_t)33))
        | !TEST(1, TEST_size_t_ge((size_t)38, (size_t)38))
        | !TEST(0, TEST_size_t_ge((size_t)33, (size_t)52)))
        goto err;
    return 1;

err:
    return 0;
}
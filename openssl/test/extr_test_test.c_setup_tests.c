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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_output_tests ; 
 int /*<<< orphan*/  test_bignum ; 
 int /*<<< orphan*/  test_bn_output ; 
 int /*<<< orphan*/  test_bool ; 
 int /*<<< orphan*/  test_char ; 
 int /*<<< orphan*/  test_int ; 
 int /*<<< orphan*/  test_long ; 
 int /*<<< orphan*/  test_long_bignum ; 
 int /*<<< orphan*/  test_long_output ; 
 int /*<<< orphan*/  test_memory ; 
 int /*<<< orphan*/  test_memory_overflow ; 
 int /*<<< orphan*/  test_messages ; 
 int /*<<< orphan*/  test_output ; 
 int /*<<< orphan*/  test_pointer ; 
 int /*<<< orphan*/  test_single_eval ; 
 int /*<<< orphan*/  test_size_t ; 
 int /*<<< orphan*/  test_skip_many ; 
 int /*<<< orphan*/  test_skip_null ; 
 int /*<<< orphan*/  test_skip_one ; 
 int /*<<< orphan*/  test_string ; 
 int /*<<< orphan*/  test_time_t ; 
 int /*<<< orphan*/  test_uchar ; 
 int /*<<< orphan*/  test_uint ; 
 int /*<<< orphan*/  test_ulong ; 

int setup_tests(void)
{
    ADD_TEST(test_int);
    ADD_TEST(test_uint);
    ADD_TEST(test_char);
    ADD_TEST(test_uchar);
    ADD_TEST(test_long);
    ADD_TEST(test_ulong);
    ADD_TEST(test_size_t);
    ADD_TEST(test_time_t);
    ADD_TEST(test_pointer);
    ADD_TEST(test_bool);
    ADD_TEST(test_string);
    ADD_TEST(test_memory);
    ADD_TEST(test_memory_overflow);
    ADD_TEST(test_bignum);
    ADD_TEST(test_long_bignum);
    ADD_TEST(test_long_output);
    ADD_TEST(test_messages);
    ADD_TEST(test_single_eval);
    ADD_TEST(test_output);
    ADD_ALL_TESTS(test_bn_output, OSSL_NELEM(bn_output_tests));
    ADD_TEST(test_skip_one);
    ADD_TEST(test_skip_null);
    ADD_ALL_TESTS(test_skip_many, 3);
    return 1;
}
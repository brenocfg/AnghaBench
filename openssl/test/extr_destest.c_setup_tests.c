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
 int NUM_TESTS ; 
 int /*<<< orphan*/  test_des_cbc ; 
 int /*<<< orphan*/  test_des_cbc_cksum ; 
 int /*<<< orphan*/  test_des_cfb16 ; 
 int /*<<< orphan*/  test_des_cfb32 ; 
 int /*<<< orphan*/  test_des_cfb48 ; 
 int /*<<< orphan*/  test_des_cfb64 ; 
 int /*<<< orphan*/  test_des_cfb8 ; 
 int /*<<< orphan*/  test_des_crypt ; 
 int /*<<< orphan*/  test_des_ecb ; 
 int /*<<< orphan*/  test_des_ede_cbc ; 
 int /*<<< orphan*/  test_des_ede_cfb64 ; 
 int /*<<< orphan*/  test_des_ede_ecb ; 
 int /*<<< orphan*/  test_des_ede_ofb64 ; 
 int /*<<< orphan*/  test_des_ofb ; 
 int /*<<< orphan*/  test_des_ofb64 ; 
 int /*<<< orphan*/  test_des_pcbc ; 
 int /*<<< orphan*/  test_des_quad_cksum ; 
 int /*<<< orphan*/  test_ede_cbc ; 
 int /*<<< orphan*/  test_input_align ; 
 int /*<<< orphan*/  test_output_align ; 

int setup_tests(void)
{
#ifndef OPENSSL_NO_DES
    ADD_ALL_TESTS(test_des_ecb, NUM_TESTS);
    ADD_TEST(test_des_cbc);
    ADD_TEST(test_ede_cbc);
    ADD_ALL_TESTS(test_des_ede_ecb, NUM_TESTS - 2);
    ADD_TEST(test_des_ede_cbc);
    ADD_TEST(test_des_pcbc);
    ADD_TEST(test_des_cfb8);
    ADD_TEST(test_des_cfb16);
    ADD_TEST(test_des_cfb32);
    ADD_TEST(test_des_cfb48);
    ADD_TEST(test_des_cfb64);
    ADD_TEST(test_des_ede_cfb64);
    ADD_TEST(test_des_ofb);
    ADD_TEST(test_des_ofb64);
    ADD_TEST(test_des_ede_ofb64);
    ADD_TEST(test_des_cbc_cksum);
    ADD_TEST(test_des_quad_cksum);
    ADD_TEST(test_des_crypt);
    ADD_ALL_TESTS(test_input_align, 4);
    ADD_ALL_TESTS(test_output_align, 4);
#endif
    return 1;
}
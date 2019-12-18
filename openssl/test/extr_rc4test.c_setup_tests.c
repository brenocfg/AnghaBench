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
 int /*<<< orphan*/  ADD_ALL_TESTS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * data_len ; 
 int /*<<< orphan*/  test_rc4_encrypt ; 
 int /*<<< orphan*/  test_rc4_end_processing ; 
 int /*<<< orphan*/  test_rc4_multi_call ; 
 int /*<<< orphan*/  test_rc_bulk ; 

int setup_tests(void)
{
#ifndef OPENSSL_NO_RC4
    ADD_ALL_TESTS(test_rc4_encrypt, OSSL_NELEM(data_len));
    ADD_ALL_TESTS(test_rc4_end_processing, data_len[3]);
    ADD_ALL_TESTS(test_rc4_multi_call, data_len[3]);
    ADD_TEST(test_rc_bulk);
#endif
    return 1;
}
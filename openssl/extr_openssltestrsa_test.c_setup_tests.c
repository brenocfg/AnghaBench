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
 int OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsa_security_bits_cases ; 
 int /*<<< orphan*/  test_rsa_oaep ; 
 int /*<<< orphan*/  test_rsa_pkcs1 ; 
 int /*<<< orphan*/  test_rsa_security_bit ; 
 int /*<<< orphan*/  test_rsa_sslv23 ; 

int setup_tests(void)
{
    ADD_ALL_TESTS(test_rsa_pkcs1, 3);
    ADD_ALL_TESTS(test_rsa_sslv23, 3);
    ADD_ALL_TESTS(test_rsa_oaep, 3);
    ADD_ALL_TESTS(test_rsa_security_bit, OSSL_NELEM(rsa_security_bits_cases));
    return 1;
}
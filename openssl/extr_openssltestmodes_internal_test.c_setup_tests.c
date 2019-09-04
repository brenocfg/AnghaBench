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
 int /*<<< orphan*/  OSSL_NELEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aes_cts128_vectors ; 
 int /*<<< orphan*/  gcm128_vectors ; 
 int /*<<< orphan*/  test_aes_cts128 ; 
 int /*<<< orphan*/  test_aes_cts128_nist ; 
 int /*<<< orphan*/  test_gcm128 ; 

int setup_tests(void)
{
    ADD_ALL_TESTS(test_aes_cts128, OSSL_NELEM(aes_cts128_vectors));
    ADD_ALL_TESTS(test_aes_cts128_nist, OSSL_NELEM(aes_cts128_vectors));
    ADD_ALL_TESTS(test_gcm128, OSSL_NELEM(gcm128_vectors));
    return 1;
}
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
 int /*<<< orphan*/  ADD_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_kdf_get_kdf ; 
 int /*<<< orphan*/  test_kdf_hkdf ; 
 int /*<<< orphan*/  test_kdf_pbkdf2 ; 
 int /*<<< orphan*/  test_kdf_scrypt ; 
 int /*<<< orphan*/  test_kdf_ss_hash ; 
 int /*<<< orphan*/  test_kdf_ss_hmac ; 
 int /*<<< orphan*/  test_kdf_ss_kmac ; 
 int /*<<< orphan*/  test_kdf_sshkdf ; 
 int /*<<< orphan*/  test_kdf_tls1_prf ; 

int setup_tests(void)
{
    ADD_TEST(test_kdf_get_kdf);
    ADD_TEST(test_kdf_tls1_prf);
    ADD_TEST(test_kdf_hkdf);
    ADD_TEST(test_kdf_pbkdf2);
#ifndef OPENSSL_NO_SCRYPT
    ADD_TEST(test_kdf_scrypt);
#endif
    ADD_TEST(test_kdf_ss_hash);
    ADD_TEST(test_kdf_ss_hmac);
    ADD_TEST(test_kdf_ss_kmac);
    ADD_TEST(test_kdf_sshkdf);
    return 1;
}
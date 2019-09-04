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
 int /*<<< orphan*/  EVP_add_kdf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hkdf_kdf_meth ; 
 int /*<<< orphan*/  pbkdf2_kdf_meth ; 
 int /*<<< orphan*/  scrypt_kdf_meth ; 
 int /*<<< orphan*/  ss_kdf_meth ; 
 int /*<<< orphan*/  sshkdf_kdf_meth ; 
 int /*<<< orphan*/  tls1_prf_kdf_meth ; 

void openssl_add_all_kdfs_int(void)
{
    EVP_add_kdf(&pbkdf2_kdf_meth);
#ifndef OPENSSL_NO_SCRYPT
    EVP_add_kdf(&scrypt_kdf_meth);
#endif
    EVP_add_kdf(&tls1_prf_kdf_meth);
    EVP_add_kdf(&hkdf_kdf_meth);
    EVP_add_kdf(&sshkdf_kdf_meth);
    EVP_add_kdf(&ss_kdf_meth);
}
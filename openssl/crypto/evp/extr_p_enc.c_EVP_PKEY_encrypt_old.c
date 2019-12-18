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
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_F_EVP_PKEY_ENCRYPT_OLD ; 
 scalar_t__ EVP_PKEY_RSA ; 
 int /*<<< orphan*/  EVP_PKEY_get0_RSA (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_R_PUBLIC_KEY_NOT_RSA ; 
 int /*<<< orphan*/  EVPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_PKCS1_PADDING ; 
 int RSA_public_encrypt (int,unsigned char const*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int EVP_PKEY_encrypt_old(unsigned char *ek, const unsigned char *key,
                         int key_len, EVP_PKEY *pubk)
{
    int ret = 0;

#ifndef OPENSSL_NO_RSA
    if (EVP_PKEY_id(pubk) != EVP_PKEY_RSA) {
#endif
        EVPerr(EVP_F_EVP_PKEY_ENCRYPT_OLD, EVP_R_PUBLIC_KEY_NOT_RSA);
#ifndef OPENSSL_NO_RSA
        goto err;
    }
    ret =
        RSA_public_encrypt(key_len, key, ek, EVP_PKEY_get0_RSA(pubk),
                           RSA_PKCS1_PADDING);
 err:
#endif
    return ret;
}
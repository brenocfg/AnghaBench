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
 int /*<<< orphan*/  ASN1_F_I2D_PUBLICKEY ; 
 int /*<<< orphan*/  ASN1_R_UNSUPPORTED_PUBLIC_KEY_TYPE ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  EVP_PKEY_DSA 130 
#define  EVP_PKEY_EC 129 
#define  EVP_PKEY_RSA 128 
 int /*<<< orphan*/  EVP_PKEY_get0_DSA (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_PKEY_get0_EC_KEY (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_PKEY_get0_RSA (int /*<<< orphan*/  const*) ; 
 int EVP_PKEY_id (int /*<<< orphan*/  const*) ; 
 int i2d_DSAPublicKey (int /*<<< orphan*/ ,unsigned char**) ; 
 int i2d_RSAPublicKey (int /*<<< orphan*/ ,unsigned char**) ; 
 int i2o_ECPublicKey (int /*<<< orphan*/ ,unsigned char**) ; 

int i2d_PublicKey(const EVP_PKEY *a, unsigned char **pp)
{
    switch (EVP_PKEY_id(a)) {
#ifndef OPENSSL_NO_RSA
    case EVP_PKEY_RSA:
        return i2d_RSAPublicKey(EVP_PKEY_get0_RSA(a), pp);
#endif
#ifndef OPENSSL_NO_DSA
    case EVP_PKEY_DSA:
        return i2d_DSAPublicKey(EVP_PKEY_get0_DSA(a), pp);
#endif
#ifndef OPENSSL_NO_EC
    case EVP_PKEY_EC:
        return i2o_ECPublicKey(EVP_PKEY_get0_EC_KEY(a), pp);
#endif
    default:
        ASN1err(ASN1_F_I2D_PUBLICKEY, ASN1_R_UNSUPPORTED_PUBLIC_KEY_TYPE);
        return -1;
    }
}
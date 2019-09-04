#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  ec; int /*<<< orphan*/  dsa; int /*<<< orphan*/ * rsa; } ;
struct TYPE_10__ {TYPE_1__ pkey; } ;
typedef  TYPE_2__ EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_D2I_PUBLICKEY ; 
 int /*<<< orphan*/  ASN1_R_UNKNOWN_PUBLIC_KEY_TYPE ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_ASN1_LIB ; 
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
#define  EVP_PKEY_DSA 130 
#define  EVP_PKEY_EC 129 
#define  EVP_PKEY_RSA 128 
 int /*<<< orphan*/  EVP_PKEY_free (TYPE_2__*) ; 
 int EVP_PKEY_id (TYPE_2__*) ; 
 TYPE_2__* EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_PKEY_set_type (TYPE_2__*,int) ; 
 int /*<<< orphan*/  d2i_DSAPublicKey (int /*<<< orphan*/ *,unsigned char const**,long) ; 
 int /*<<< orphan*/ * d2i_RSAPublicKey (int /*<<< orphan*/ *,unsigned char const**,long) ; 
 int /*<<< orphan*/  o2i_ECPublicKey (int /*<<< orphan*/ *,unsigned char const**,long) ; 

EVP_PKEY *d2i_PublicKey(int type, EVP_PKEY **a, const unsigned char **pp,
                        long length)
{
    EVP_PKEY *ret;

    if ((a == NULL) || (*a == NULL)) {
        if ((ret = EVP_PKEY_new()) == NULL) {
            ASN1err(ASN1_F_D2I_PUBLICKEY, ERR_R_EVP_LIB);
            return NULL;
        }
    } else
        ret = *a;

    if (type != EVP_PKEY_id(ret) && !EVP_PKEY_set_type(ret, type)) {
        ASN1err(ASN1_F_D2I_PUBLICKEY, ERR_R_EVP_LIB);
        goto err;
    }

    switch (EVP_PKEY_id(ret)) {
#ifndef OPENSSL_NO_RSA
    case EVP_PKEY_RSA:
        if ((ret->pkey.rsa = d2i_RSAPublicKey(NULL, pp, length)) == NULL) {
            ASN1err(ASN1_F_D2I_PUBLICKEY, ERR_R_ASN1_LIB);
            goto err;
        }
        break;
#endif
#ifndef OPENSSL_NO_DSA
    case EVP_PKEY_DSA:
        /* TMP UGLY CAST */
        if (!d2i_DSAPublicKey(&ret->pkey.dsa, pp, length)) {
            ASN1err(ASN1_F_D2I_PUBLICKEY, ERR_R_ASN1_LIB);
            goto err;
        }
        break;
#endif
#ifndef OPENSSL_NO_EC
    case EVP_PKEY_EC:
        if (!o2i_ECPublicKey(&ret->pkey.ec, pp, length)) {
            ASN1err(ASN1_F_D2I_PUBLICKEY, ERR_R_ASN1_LIB);
            goto err;
        }
        break;
#endif
    default:
        ASN1err(ASN1_F_D2I_PUBLICKEY, ASN1_R_UNKNOWN_PUBLIC_KEY_TYPE);
        goto err;
    }
    if (a != NULL)
        (*a) = ret;
    return ret;
 err:
    if (a == NULL || *a != ret)
        EVP_PKEY_free(ret);
    return NULL;
}
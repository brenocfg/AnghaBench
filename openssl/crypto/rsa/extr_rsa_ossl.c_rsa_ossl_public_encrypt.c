#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int /*<<< orphan*/  _method_mod_n; int /*<<< orphan*/ * n; int /*<<< orphan*/ * e; TYPE_1__* meth; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* bn_mod_exp ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ RSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_MONT_CTX_set_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int BN_bn2binpad (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/ *) ; 
 int BN_num_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_ucmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ OPENSSL_RSA_MAX_MODULUS_BITS ; 
 scalar_t__ OPENSSL_RSA_MAX_PUBEXP_BITS ; 
 scalar_t__ OPENSSL_RSA_SMALL_MODULUS_BITS ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,int) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int RSA_FLAG_CACHE_PUBLIC ; 
 int /*<<< orphan*/  RSA_F_RSA_OSSL_PUBLIC_ENCRYPT ; 
#define  RSA_NO_PADDING 131 
#define  RSA_PKCS1_OAEP_PADDING 130 
#define  RSA_PKCS1_PADDING 129 
 int /*<<< orphan*/  RSA_R_BAD_E_VALUE ; 
 int /*<<< orphan*/  RSA_R_DATA_TOO_LARGE_FOR_MODULUS ; 
 int /*<<< orphan*/  RSA_R_MODULUS_TOO_LARGE ; 
 int /*<<< orphan*/  RSA_R_UNKNOWN_PADDING_TYPE ; 
#define  RSA_SSLV23_PADDING 128 
 int RSA_padding_add_PKCS1_OAEP (unsigned char*,int,unsigned char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RSA_padding_add_PKCS1_type_2 (unsigned char*,int,unsigned char const*,int) ; 
 int RSA_padding_add_SSLv23 (unsigned char*,int,unsigned char const*,int) ; 
 int RSA_padding_add_none (unsigned char*,int,unsigned char const*,int) ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsa_ossl_public_encrypt(int flen, const unsigned char *from,
                                  unsigned char *to, RSA *rsa, int padding)
{
    BIGNUM *f, *ret;
    int i, num = 0, r = -1;
    unsigned char *buf = NULL;
    BN_CTX *ctx = NULL;

    if (BN_num_bits(rsa->n) > OPENSSL_RSA_MAX_MODULUS_BITS) {
        RSAerr(RSA_F_RSA_OSSL_PUBLIC_ENCRYPT, RSA_R_MODULUS_TOO_LARGE);
        return -1;
    }

    if (BN_ucmp(rsa->n, rsa->e) <= 0) {
        RSAerr(RSA_F_RSA_OSSL_PUBLIC_ENCRYPT, RSA_R_BAD_E_VALUE);
        return -1;
    }

    /* for large moduli, enforce exponent limit */
    if (BN_num_bits(rsa->n) > OPENSSL_RSA_SMALL_MODULUS_BITS) {
        if (BN_num_bits(rsa->e) > OPENSSL_RSA_MAX_PUBEXP_BITS) {
            RSAerr(RSA_F_RSA_OSSL_PUBLIC_ENCRYPT, RSA_R_BAD_E_VALUE);
            return -1;
        }
    }

    if ((ctx = BN_CTX_new()) == NULL)
        goto err;
    BN_CTX_start(ctx);
    f = BN_CTX_get(ctx);
    ret = BN_CTX_get(ctx);
    num = BN_num_bytes(rsa->n);
    buf = OPENSSL_malloc(num);
    if (ret == NULL || buf == NULL) {
        RSAerr(RSA_F_RSA_OSSL_PUBLIC_ENCRYPT, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    switch (padding) {
    case RSA_PKCS1_PADDING:
        i = RSA_padding_add_PKCS1_type_2(buf, num, from, flen);
        break;
    case RSA_PKCS1_OAEP_PADDING:
        i = RSA_padding_add_PKCS1_OAEP(buf, num, from, flen, NULL, 0);
        break;
    case RSA_SSLV23_PADDING:
        i = RSA_padding_add_SSLv23(buf, num, from, flen);
        break;
    case RSA_NO_PADDING:
        i = RSA_padding_add_none(buf, num, from, flen);
        break;
    default:
        RSAerr(RSA_F_RSA_OSSL_PUBLIC_ENCRYPT, RSA_R_UNKNOWN_PADDING_TYPE);
        goto err;
    }
    if (i <= 0)
        goto err;

    if (BN_bin2bn(buf, num, f) == NULL)
        goto err;

    if (BN_ucmp(f, rsa->n) >= 0) {
        /* usually the padding functions would catch this */
        RSAerr(RSA_F_RSA_OSSL_PUBLIC_ENCRYPT,
               RSA_R_DATA_TOO_LARGE_FOR_MODULUS);
        goto err;
    }

    if (rsa->flags & RSA_FLAG_CACHE_PUBLIC)
        if (!BN_MONT_CTX_set_locked(&rsa->_method_mod_n, rsa->lock,
                                    rsa->n, ctx))
            goto err;

    if (!rsa->meth->bn_mod_exp(ret, f, rsa->e, rsa->n, ctx,
                               rsa->_method_mod_n))
        goto err;

    /*
     * BN_bn2binpad puts in leading 0 bytes if the number is less than
     * the length of the modulus.
     */
    r = BN_bn2binpad(ret, to, num);
 err:
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    OPENSSL_clear_free(buf, num);
    return r;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; scalar_t__ version; int /*<<< orphan*/  n; int /*<<< orphan*/  _method_mod_n; TYPE_1__* meth; int /*<<< orphan*/ * d; int /*<<< orphan*/ * iqmp; int /*<<< orphan*/ * dmq1; int /*<<< orphan*/ * dmp1; int /*<<< orphan*/ * q; int /*<<< orphan*/ * p; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* bn_mod_exp ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* rsa_mod_exp ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ RSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BN_BLINDING ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_MONT_CTX_set_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int BN_bn2binpad (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int BN_num_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_ucmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_with_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,int) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 scalar_t__ RSA_ASN1_VERSION_MULTI ; 
 int RSA_FLAG_CACHE_PUBLIC ; 
 int RSA_FLAG_EXT_PKEY ; 
 int RSA_FLAG_NO_BLINDING ; 
 int /*<<< orphan*/  RSA_F_RSA_OSSL_PRIVATE_ENCRYPT ; 
#define  RSA_NO_PADDING 131 
#define  RSA_PKCS1_PADDING 130 
 int /*<<< orphan*/  RSA_R_DATA_TOO_LARGE_FOR_MODULUS ; 
 int /*<<< orphan*/  RSA_R_MISSING_PRIVATE_KEY ; 
 int /*<<< orphan*/  RSA_R_UNKNOWN_PADDING_TYPE ; 
#define  RSA_SSLV23_PADDING 129 
#define  RSA_X931_PADDING 128 
 int RSA_padding_add_PKCS1_type_1 (unsigned char*,int,unsigned char const*,int) ; 
 int RSA_padding_add_X931 (unsigned char*,int,unsigned char const*,int) ; 
 int RSA_padding_add_none (unsigned char*,int,unsigned char const*,int) ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsa_blinding_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsa_blinding_invert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rsa_get_blinding (TYPE_2__*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsa_ossl_private_encrypt(int flen, const unsigned char *from,
                                   unsigned char *to, RSA *rsa, int padding)
{
    BIGNUM *f, *ret, *res;
    int i, num = 0, r = -1;
    unsigned char *buf = NULL;
    BN_CTX *ctx = NULL;
    int local_blinding = 0;
    /*
     * Used only if the blinding structure is shared. A non-NULL unblind
     * instructs rsa_blinding_convert() and rsa_blinding_invert() to store
     * the unblinding factor outside the blinding structure.
     */
    BIGNUM *unblind = NULL;
    BN_BLINDING *blinding = NULL;

    if ((ctx = BN_CTX_new()) == NULL)
        goto err;
    BN_CTX_start(ctx);
    f = BN_CTX_get(ctx);
    ret = BN_CTX_get(ctx);
    num = BN_num_bytes(rsa->n);
    buf = OPENSSL_malloc(num);
    if (ret == NULL || buf == NULL) {
        RSAerr(RSA_F_RSA_OSSL_PRIVATE_ENCRYPT, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    switch (padding) {
    case RSA_PKCS1_PADDING:
        i = RSA_padding_add_PKCS1_type_1(buf, num, from, flen);
        break;
    case RSA_X931_PADDING:
        i = RSA_padding_add_X931(buf, num, from, flen);
        break;
    case RSA_NO_PADDING:
        i = RSA_padding_add_none(buf, num, from, flen);
        break;
    case RSA_SSLV23_PADDING:
    default:
        RSAerr(RSA_F_RSA_OSSL_PRIVATE_ENCRYPT, RSA_R_UNKNOWN_PADDING_TYPE);
        goto err;
    }
    if (i <= 0)
        goto err;

    if (BN_bin2bn(buf, num, f) == NULL)
        goto err;

    if (BN_ucmp(f, rsa->n) >= 0) {
        /* usually the padding functions would catch this */
        RSAerr(RSA_F_RSA_OSSL_PRIVATE_ENCRYPT,
               RSA_R_DATA_TOO_LARGE_FOR_MODULUS);
        goto err;
    }

    if (rsa->flags & RSA_FLAG_CACHE_PUBLIC)
        if (!BN_MONT_CTX_set_locked(&rsa->_method_mod_n, rsa->lock,
                                    rsa->n, ctx))
            goto err;

    if (!(rsa->flags & RSA_FLAG_NO_BLINDING)) {
        blinding = rsa_get_blinding(rsa, &local_blinding, ctx);
        if (blinding == NULL) {
            RSAerr(RSA_F_RSA_OSSL_PRIVATE_ENCRYPT, ERR_R_INTERNAL_ERROR);
            goto err;
        }
    }

    if (blinding != NULL) {
        if (!local_blinding && ((unblind = BN_CTX_get(ctx)) == NULL)) {
            RSAerr(RSA_F_RSA_OSSL_PRIVATE_ENCRYPT, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        if (!rsa_blinding_convert(blinding, f, unblind, ctx))
            goto err;
    }

    if ((rsa->flags & RSA_FLAG_EXT_PKEY) ||
        (rsa->version == RSA_ASN1_VERSION_MULTI) ||
        ((rsa->p != NULL) &&
         (rsa->q != NULL) &&
         (rsa->dmp1 != NULL) && (rsa->dmq1 != NULL) && (rsa->iqmp != NULL))) {
        if (!rsa->meth->rsa_mod_exp(ret, f, rsa, ctx))
            goto err;
    } else {
        BIGNUM *d = BN_new();
        if (d == NULL) {
            RSAerr(RSA_F_RSA_OSSL_PRIVATE_ENCRYPT, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        if (rsa->d == NULL) {
            RSAerr(RSA_F_RSA_OSSL_PRIVATE_ENCRYPT, RSA_R_MISSING_PRIVATE_KEY);
            BN_free(d);
            goto err;
        }
        BN_with_flags(d, rsa->d, BN_FLG_CONSTTIME);

        if (!rsa->meth->bn_mod_exp(ret, f, d, rsa->n, ctx,
                                   rsa->_method_mod_n)) {
            BN_free(d);
            goto err;
        }
        /* We MUST free d before any further use of rsa->d */
        BN_free(d);
    }

    if (blinding)
        if (!rsa_blinding_invert(blinding, ret, unblind, ctx))
            goto err;

    if (padding == RSA_X931_PADDING) {
        if (!BN_sub(f, rsa->n, ret))
            goto err;
        if (BN_cmp(ret, f) > 0)
            res = f;
        else
            res = ret;
    } else {
        res = ret;
    }

    /*
     * BN_bn2binpad puts in leading 0 bytes if the number is less than
     * the length of the modulus.
     */
    r = BN_bn2binpad(res, to, num);
 err:
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    OPENSSL_clear_free(buf, num);
    return r;
}
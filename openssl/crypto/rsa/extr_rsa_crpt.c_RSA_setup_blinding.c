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
struct TYPE_5__ {int /*<<< orphan*/ * e; int /*<<< orphan*/  _method_mod_n; TYPE_1__* meth; int /*<<< orphan*/  n; int /*<<< orphan*/  q; int /*<<< orphan*/  p; int /*<<< orphan*/  d; } ;
struct TYPE_4__ {int /*<<< orphan*/  bn_mod_exp; } ;
typedef  TYPE_2__ RSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BN_BLINDING ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_BLINDING_create_param (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_BLINDING_set_current_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_with_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  RSA_F_RSA_SETUP_BLINDING ; 
 int /*<<< orphan*/  RSA_R_NO_PUBLIC_EXPONENT ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rsa_get_public_exp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

BN_BLINDING *RSA_setup_blinding(RSA *rsa, BN_CTX *in_ctx)
{
    BIGNUM *e;
    BN_CTX *ctx;
    BN_BLINDING *ret = NULL;

    if (in_ctx == NULL) {
        if ((ctx = BN_CTX_new()) == NULL)
            return 0;
    } else {
        ctx = in_ctx;
    }

    BN_CTX_start(ctx);
    e = BN_CTX_get(ctx);
    if (e == NULL) {
        RSAerr(RSA_F_RSA_SETUP_BLINDING, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (rsa->e == NULL) {
        e = rsa_get_public_exp(rsa->d, rsa->p, rsa->q, ctx);
        if (e == NULL) {
            RSAerr(RSA_F_RSA_SETUP_BLINDING, RSA_R_NO_PUBLIC_EXPONENT);
            goto err;
        }
    } else {
        e = rsa->e;
    }

    {
        BIGNUM *n = BN_new();

        if (n == NULL) {
            RSAerr(RSA_F_RSA_SETUP_BLINDING, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        BN_with_flags(n, rsa->n, BN_FLG_CONSTTIME);

        ret = BN_BLINDING_create_param(NULL, e, n, ctx, rsa->meth->bn_mod_exp,
                                       rsa->_method_mod_n);
        /* We MUST free n before any further use of rsa->n */
        BN_free(n);
    }
    if (ret == NULL) {
        RSAerr(RSA_F_RSA_SETUP_BLINDING, ERR_R_BN_LIB);
        goto err;
    }

    BN_BLINDING_set_current_thread(ret);

 err:
    BN_CTX_end(ctx);
    if (ctx != in_ctx)
        BN_CTX_free(ctx);
    if (e != rsa->e)
        BN_free(e);

    return ret;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dirty_cnt; int /*<<< orphan*/ * q; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ RSA ;
typedef  int /*<<< orphan*/  BN_GENCB ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_X931_generate_Xpq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_X931_generate_prime_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* BN_new () ; 
 int /*<<< orphan*/  RSA_X931_derive_ex (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int RSA_X931_generate_key_ex(RSA *rsa, int bits, const BIGNUM *e,
                             BN_GENCB *cb)
{
    int ok = 0;
    BIGNUM *Xp = NULL, *Xq = NULL;
    BN_CTX *ctx = NULL;

    ctx = BN_CTX_new();
    if (ctx == NULL)
        goto error;

    BN_CTX_start(ctx);
    Xp = BN_CTX_get(ctx);
    Xq = BN_CTX_get(ctx);
    if (Xq == NULL)
        goto error;
    if (!BN_X931_generate_Xpq(Xp, Xq, bits, ctx))
        goto error;

    rsa->p = BN_new();
    rsa->q = BN_new();
    if (rsa->p == NULL || rsa->q == NULL)
        goto error;

    /* Generate two primes from Xp, Xq */

    if (!BN_X931_generate_prime_ex(rsa->p, NULL, NULL, NULL, NULL, Xp,
                                   e, ctx, cb))
        goto error;

    if (!BN_X931_generate_prime_ex(rsa->q, NULL, NULL, NULL, NULL, Xq,
                                   e, ctx, cb))
        goto error;

    /*
     * Since rsa->p and rsa->q are valid this call will just derive remaining
     * RSA components.
     */

    if (!RSA_X931_derive_ex(rsa, NULL, NULL, NULL, NULL,
                            NULL, NULL, NULL, NULL, NULL, NULL, e, cb))
        goto error;

    rsa->dirty_cnt++;
    ok = 1;

 error:
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);

    if (ok)
        return 1;

    return 0;

}
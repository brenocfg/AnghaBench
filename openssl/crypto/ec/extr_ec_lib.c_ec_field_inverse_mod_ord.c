#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * mont_data; int /*<<< orphan*/  order; } ;
typedef  TYPE_1__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_secure_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp_mont (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ec_field_inverse_mod_ord(const EC_GROUP *group, BIGNUM *r,
                                    const BIGNUM *x, BN_CTX *ctx)
{
    BIGNUM *e = NULL;
    int ret = 0;
#ifndef FIPS_MODE
    BN_CTX *new_ctx = NULL;

    if (ctx == NULL)
        ctx = new_ctx = BN_CTX_secure_new();
#endif
    if (ctx == NULL)
        return 0;

    if (group->mont_data == NULL)
        goto err;

    BN_CTX_start(ctx);
    if ((e = BN_CTX_get(ctx)) == NULL)
        goto err;

    /*-
     * We want inverse in constant time, therefore we utilize the fact
     * order must be prime and use Fermats Little Theorem instead.
     */
    if (!BN_set_word(e, 2))
        goto err;
    if (!BN_sub(e, group->order, e))
        goto err;
    /*-
     * Exponent e is public.
     * No need for scatter-gather or BN_FLG_CONSTTIME.
     */
    if (!BN_mod_exp_mont(r, x, e, group->order, ctx, group->mont_data))
        goto err;

    ret = 1;

 err:
    BN_CTX_end(ctx);
#ifndef FIPS_MODE
    BN_CTX_free(new_ctx);
#endif
    return ret;
}
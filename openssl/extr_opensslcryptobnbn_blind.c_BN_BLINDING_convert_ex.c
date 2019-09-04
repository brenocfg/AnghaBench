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
struct TYPE_4__ {int counter; int /*<<< orphan*/  mod; int /*<<< orphan*/ * A; int /*<<< orphan*/ * m_ctx; int /*<<< orphan*/ * Ai; } ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  TYPE_1__ BN_BLINDING ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_BLINDING_update (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_F_BN_BLINDING_CONVERT_EX ; 
 int /*<<< orphan*/  BN_R_NOT_INITIALIZED ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BN_mod_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int BN_mod_mul_montgomery (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/ *) ; 

int BN_BLINDING_convert_ex(BIGNUM *n, BIGNUM *r, BN_BLINDING *b, BN_CTX *ctx)
{
    int ret = 1;

    bn_check_top(n);

    if ((b->A == NULL) || (b->Ai == NULL)) {
        BNerr(BN_F_BN_BLINDING_CONVERT_EX, BN_R_NOT_INITIALIZED);
        return 0;
    }

    if (b->counter == -1)
        /* Fresh blinding, doesn't need updating. */
        b->counter = 0;
    else if (!BN_BLINDING_update(b, ctx))
        return 0;

    if (r != NULL && (BN_copy(r, b->Ai) == NULL))
        return 0;

    if (b->m_ctx != NULL)
        ret = BN_mod_mul_montgomery(n, n, b->A, b->m_ctx, ctx);
    else
        ret = BN_mod_mul(n, n, b->A, b->mod, ctx);

    return ret;
}
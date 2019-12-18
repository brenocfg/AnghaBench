#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ntop ;
typedef  int /*<<< orphan*/  i ;
struct TYPE_14__ {size_t dmax; size_t top; size_t* d; size_t flags; } ;
struct TYPE_13__ {int /*<<< orphan*/  mod; int /*<<< orphan*/ * m_ctx; TYPE_2__* Ai; } ;
typedef  size_t BN_ULONG ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  TYPE_1__ BN_BLINDING ;
typedef  TYPE_2__ BIGNUM ;

/* Variables and functions */
 size_t BN_FLG_FIXED_TOP ; 
 int /*<<< orphan*/  BN_F_BN_BLINDING_INVERT_EX ; 
 int /*<<< orphan*/  BN_R_NOT_INITIALIZED ; 
 int BN_mod_mul (TYPE_2__*,TYPE_2__*,TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int BN_mod_mul_montgomery (TYPE_2__*,TYPE_2__*,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_check_top (TYPE_2__*) ; 

int BN_BLINDING_invert_ex(BIGNUM *n, const BIGNUM *r, BN_BLINDING *b,
                          BN_CTX *ctx)
{
    int ret;

    bn_check_top(n);

    if (r == NULL && (r = b->Ai) == NULL) {
        BNerr(BN_F_BN_BLINDING_INVERT_EX, BN_R_NOT_INITIALIZED);
        return 0;
    }

    if (b->m_ctx != NULL) {
        /* ensure that BN_mod_mul_montgomery takes pre-defined path */
        if (n->dmax >= r->top) {
            size_t i, rtop = r->top, ntop = n->top;
            BN_ULONG mask;

            for (i = 0; i < rtop; i++) {
                mask = (BN_ULONG)0 - ((i - ntop) >> (8 * sizeof(i) - 1));
                n->d[i] &= mask;
            }
            mask = (BN_ULONG)0 - ((rtop - ntop) >> (8 * sizeof(ntop) - 1));
            /* always true, if (rtop >= ntop) n->top = r->top; */
            n->top = (int)(rtop & ~mask) | (ntop & mask);
            n->flags |= (BN_FLG_FIXED_TOP & ~mask);
        }
        ret = BN_mod_mul_montgomery(n, n, r, b->m_ctx, ctx);
    } else {
        ret = BN_mod_mul(n, n, r, b->mod, ctx);
    }

    bn_check_top(n);
    return ret;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_27__ {int top; scalar_t__ neg; } ;
struct TYPE_26__ {int top; int /*<<< orphan*/  flags; scalar_t__* d; } ;
struct TYPE_25__ {int ri; TYPE_2__ RR; TYPE_5__ N; int /*<<< orphan*/  Ni; } ;
typedef  TYPE_1__ BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  TYPE_2__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 TYPE_2__* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_FLG_FIXED_TOP ; 
 int /*<<< orphan*/  BN_copy (TYPE_5__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_get_flags (TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ BN_is_zero (TYPE_2__ const*) ; 
 int /*<<< orphan*/  BN_lshift (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  BN_mod (TYPE_2__*,TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_mod_inverse (TYPE_2__*,TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int BN_num_bits (TYPE_5__*) ; 
 int /*<<< orphan*/  BN_set_bit (TYPE_2__*,int) ; 
 int /*<<< orphan*/  BN_set_flags (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_sub_word (TYPE_2__*,int) ; 
 int /*<<< orphan*/  BN_zero (TYPE_2__*) ; 

int BN_MONT_CTX_set(BN_MONT_CTX *mont, const BIGNUM *mod, BN_CTX *ctx)
{
    int i, ret = 0;
    BIGNUM *Ri, *R;

    if (BN_is_zero(mod))
        return 0;

    BN_CTX_start(ctx);
    if ((Ri = BN_CTX_get(ctx)) == NULL)
        goto err;
    R = &(mont->RR);            /* grab RR as a temp */
    if (!BN_copy(&(mont->N), mod))
        goto err;               /* Set N */
    if (BN_get_flags(mod, BN_FLG_CONSTTIME) != 0)
        BN_set_flags(&(mont->N), BN_FLG_CONSTTIME);
    mont->N.neg = 0;

#ifdef MONT_WORD
    {
        BIGNUM tmod;
        BN_ULONG buf[2];

        bn_init(&tmod);
        tmod.d = buf;
        tmod.dmax = 2;
        tmod.neg = 0;

        if (BN_get_flags(mod, BN_FLG_CONSTTIME) != 0)
            BN_set_flags(&tmod, BN_FLG_CONSTTIME);

        mont->ri = (BN_num_bits(mod) + (BN_BITS2 - 1)) / BN_BITS2 * BN_BITS2;

# if defined(OPENSSL_BN_ASM_MONT) && (BN_BITS2<=32)
        /*
         * Only certain BN_BITS2<=32 platforms actually make use of n0[1],
         * and we could use the #else case (with a shorter R value) for the
         * others.  However, currently only the assembler files do know which
         * is which.
         */

        BN_zero(R);
        if (!(BN_set_bit(R, 2 * BN_BITS2)))
            goto err;

        tmod.top = 0;
        if ((buf[0] = mod->d[0]))
            tmod.top = 1;
        if ((buf[1] = mod->top > 1 ? mod->d[1] : 0))
            tmod.top = 2;

        if (BN_is_one(&tmod))
            BN_zero(Ri);
        else if ((BN_mod_inverse(Ri, R, &tmod, ctx)) == NULL)
            goto err;
        if (!BN_lshift(Ri, Ri, 2 * BN_BITS2))
            goto err;           /* R*Ri */
        if (!BN_is_zero(Ri)) {
            if (!BN_sub_word(Ri, 1))
                goto err;
        } else {                /* if N mod word size == 1 */

            if (bn_expand(Ri, (int)sizeof(BN_ULONG) * 2) == NULL)
                goto err;
            /* Ri-- (mod double word size) */
            Ri->neg = 0;
            Ri->d[0] = BN_MASK2;
            Ri->d[1] = BN_MASK2;
            Ri->top = 2;
        }
        if (!BN_div(Ri, NULL, Ri, &tmod, ctx))
            goto err;
        /*
         * Ni = (R*Ri-1)/N, keep only couple of least significant words:
         */
        mont->n0[0] = (Ri->top > 0) ? Ri->d[0] : 0;
        mont->n0[1] = (Ri->top > 1) ? Ri->d[1] : 0;
# else
        BN_zero(R);
        if (!(BN_set_bit(R, BN_BITS2)))
            goto err;           /* R */

        buf[0] = mod->d[0];     /* tmod = N mod word size */
        buf[1] = 0;
        tmod.top = buf[0] != 0 ? 1 : 0;
        /* Ri = R^-1 mod N */
        if (BN_is_one(&tmod))
            BN_zero(Ri);
        else if ((BN_mod_inverse(Ri, R, &tmod, ctx)) == NULL)
            goto err;
        if (!BN_lshift(Ri, Ri, BN_BITS2))
            goto err;           /* R*Ri */
        if (!BN_is_zero(Ri)) {
            if (!BN_sub_word(Ri, 1))
                goto err;
        } else {                /* if N mod word size == 1 */

            if (!BN_set_word(Ri, BN_MASK2))
                goto err;       /* Ri-- (mod word size) */
        }
        if (!BN_div(Ri, NULL, Ri, &tmod, ctx))
            goto err;
        /*
         * Ni = (R*Ri-1)/N, keep only least significant word:
         */
        mont->n0[0] = (Ri->top > 0) ? Ri->d[0] : 0;
        mont->n0[1] = 0;
# endif
    }
#else                           /* !MONT_WORD */
    {                           /* bignum version */
        mont->ri = BN_num_bits(&mont->N);
        BN_zero(R);
        if (!BN_set_bit(R, mont->ri))
            goto err;           /* R = 2^ri */
        /* Ri = R^-1 mod N */
        if ((BN_mod_inverse(Ri, R, &mont->N, ctx)) == NULL)
            goto err;
        if (!BN_lshift(Ri, Ri, mont->ri))
            goto err;           /* R*Ri */
        if (!BN_sub_word(Ri, 1))
            goto err;
        /*
         * Ni = (R*Ri-1) / N
         */
        if (!BN_div(&(mont->Ni), NULL, Ri, &mont->N, ctx))
            goto err;
    }
#endif

    /* setup RR for conversions */
    BN_zero(&(mont->RR));
    if (!BN_set_bit(&(mont->RR), mont->ri * 2))
        goto err;
    if (!BN_mod(&(mont->RR), &(mont->RR), &(mont->N), ctx))
        goto err;

    for (i = mont->RR.top, ret = mont->N.top; i < ret; i++)
        mont->RR.d[i] = 0;
    mont->RR.top = ret;
    mont->RR.flags |= BN_FLG_FIXED_TOP;

    ret = 1;
 err:
    BN_CTX_end(ctx);
    return ret;
}
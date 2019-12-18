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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_RAND_BOTTOM_ANY ; 
 int /*<<< orphan*/  BN_RAND_TOP_TWO ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_priv_rand_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int BN_X931_generate_Xpq(BIGNUM *Xp, BIGNUM *Xq, int nbits, BN_CTX *ctx)
{
    BIGNUM *t;
    int i;
    /*
     * Number of bits for each prime is of the form 512+128s for s = 0, 1,
     * ...
     */
    if ((nbits < 1024) || (nbits & 0xff))
        return 0;
    nbits >>= 1;
    /*
     * The random value Xp must be between sqrt(2) * 2^(nbits-1) and 2^nbits
     * - 1. By setting the top two bits we ensure that the lower bound is
     * exceeded.
     */
    if (!BN_priv_rand_ex(Xp, nbits, BN_RAND_TOP_TWO, BN_RAND_BOTTOM_ANY, ctx))
        goto err;

    BN_CTX_start(ctx);
    t = BN_CTX_get(ctx);
    if (t == NULL)
        goto err;

    for (i = 0; i < 1000; i++) {
        if (!BN_priv_rand_ex(Xq, nbits, BN_RAND_TOP_TWO, BN_RAND_BOTTOM_ANY,
                             ctx))
            goto err;

        /* Check that |Xp - Xq| > 2^(nbits - 100) */
        if (!BN_sub(t, Xp, Xq))
            goto err;
        if (BN_num_bits(t) > (nbits - 100))
            break;
    }

    BN_CTX_end(ctx);

    if (i < 1000)
        return 1;

    return 0;

 err:
    BN_CTX_end(ctx);
    return 0;
}
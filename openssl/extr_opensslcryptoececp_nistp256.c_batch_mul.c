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
typedef  int u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  smallfelem ;
typedef  int /*<<< orphan*/  nq ;
typedef  scalar_t__ limb ;
typedef  int const* felem_bytearray ;
typedef  int /*<<< orphan*/  felem ;

/* Variables and functions */
 int /*<<< orphan*/  copy_small_conditional (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ec_GFp_nistp_recode_scalar_bits (int*,int*,int) ; 
 int /*<<< orphan*/  felem_assign (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_contract (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_bit (int const* const,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  point_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  point_double (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_point (int,int,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smallfelem_expand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smallfelem_neg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batch_mul(felem x_out, felem y_out, felem z_out,
                      const felem_bytearray scalars[],
                      const unsigned num_points, const u8 *g_scalar,
                      const int mixed, const smallfelem pre_comp[][17][3],
                      const smallfelem g_pre_comp[2][16][3])
{
    int i, skip;
    unsigned num, gen_mul = (g_scalar != NULL);
    felem nq[3], ftmp;
    smallfelem tmp[3];
    u64 bits;
    u8 sign, digit;

    /* set nq to the point at infinity */
    memset(nq, 0, sizeof(nq));

    /*
     * Loop over all scalars msb-to-lsb, interleaving additions of multiples
     * of the generator (two in each of the last 32 rounds) and additions of
     * other points multiples (every 5th round).
     */
    skip = 1;                   /* save two point operations in the first
                                 * round */
    for (i = (num_points ? 255 : 31); i >= 0; --i) {
        /* double */
        if (!skip)
            point_double(nq[0], nq[1], nq[2], nq[0], nq[1], nq[2]);

        /* add multiples of the generator */
        if (gen_mul && (i <= 31)) {
            /* first, look 32 bits upwards */
            bits = get_bit(g_scalar, i + 224) << 3;
            bits |= get_bit(g_scalar, i + 160) << 2;
            bits |= get_bit(g_scalar, i + 96) << 1;
            bits |= get_bit(g_scalar, i + 32);
            /* select the point to add, in constant time */
            select_point(bits, 16, g_pre_comp[1], tmp);

            if (!skip) {
                /* Arg 1 below is for "mixed" */
                point_add(nq[0], nq[1], nq[2],
                          nq[0], nq[1], nq[2], 1, tmp[0], tmp[1], tmp[2]);
            } else {
                smallfelem_expand(nq[0], tmp[0]);
                smallfelem_expand(nq[1], tmp[1]);
                smallfelem_expand(nq[2], tmp[2]);
                skip = 0;
            }

            /* second, look at the current position */
            bits = get_bit(g_scalar, i + 192) << 3;
            bits |= get_bit(g_scalar, i + 128) << 2;
            bits |= get_bit(g_scalar, i + 64) << 1;
            bits |= get_bit(g_scalar, i);
            /* select the point to add, in constant time */
            select_point(bits, 16, g_pre_comp[0], tmp);
            /* Arg 1 below is for "mixed" */
            point_add(nq[0], nq[1], nq[2],
                      nq[0], nq[1], nq[2], 1, tmp[0], tmp[1], tmp[2]);
        }

        /* do other additions every 5 doublings */
        if (num_points && (i % 5 == 0)) {
            /* loop over all scalars */
            for (num = 0; num < num_points; ++num) {
                bits = get_bit(scalars[num], i + 4) << 5;
                bits |= get_bit(scalars[num], i + 3) << 4;
                bits |= get_bit(scalars[num], i + 2) << 3;
                bits |= get_bit(scalars[num], i + 1) << 2;
                bits |= get_bit(scalars[num], i) << 1;
                bits |= get_bit(scalars[num], i - 1);
                ec_GFp_nistp_recode_scalar_bits(&sign, &digit, bits);

                /*
                 * select the point to add or subtract, in constant time
                 */
                select_point(digit, 17, pre_comp[num], tmp);
                smallfelem_neg(ftmp, tmp[1]); /* (X, -Y, Z) is the negative
                                               * point */
                copy_small_conditional(ftmp, tmp[1], (((limb) sign) - 1));
                felem_contract(tmp[1], ftmp);

                if (!skip) {
                    point_add(nq[0], nq[1], nq[2],
                              nq[0], nq[1], nq[2],
                              mixed, tmp[0], tmp[1], tmp[2]);
                } else {
                    smallfelem_expand(nq[0], tmp[0]);
                    smallfelem_expand(nq[1], tmp[1]);
                    smallfelem_expand(nq[2], tmp[2]);
                    skip = 0;
                }
            }
        }
    }
    felem_assign(x_out, nq[0]);
    felem_assign(y_out, nq[1]);
    felem_assign(z_out, nq[2]);
}
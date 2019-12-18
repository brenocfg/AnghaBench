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
typedef  int BN_ULONG ;

/* Variables and functions */
 int BN_MASK2 ; 
 int BN_MUL_RECURSIVE_SIZE_NORMAL ; 
 scalar_t__ bn_add_words (int*,int*,int*,int) ; 
 int bn_cmp_part_words (int*,int*,int,int) ; 
 int /*<<< orphan*/  bn_mul_comba4 (int*,int*,int*) ; 
 int /*<<< orphan*/  bn_mul_comba8 (int*,int*,int*) ; 
 int /*<<< orphan*/  bn_mul_normal (int*,int*,int,int*,int) ; 
 int /*<<< orphan*/  bn_mul_recursive (int*,int*,int*,int,int,int,int*) ; 
 int /*<<< orphan*/  bn_sub_part_words (int*,int*,int*,int,int) ; 
 scalar_t__ bn_sub_words (int*,int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int tn ; 

void bn_mul_part_recursive(BN_ULONG *r, BN_ULONG *a, BN_ULONG *b, int n,
                           int tna, int tnb, BN_ULONG *t)
{
    int i, j, n2 = n * 2;
    int c1, c2, neg;
    BN_ULONG ln, lo, *p;

    if (n < 8) {
        bn_mul_normal(r, a, n + tna, b, n + tnb);
        return;
    }

    /* r=(a[0]-a[1])*(b[1]-b[0]) */
    c1 = bn_cmp_part_words(a, &(a[n]), tna, n - tna);
    c2 = bn_cmp_part_words(&(b[n]), b, tnb, tnb - n);
    neg = 0;
    switch (c1 * 3 + c2) {
    case -4:
        bn_sub_part_words(t, &(a[n]), a, tna, tna - n); /* - */
        bn_sub_part_words(&(t[n]), b, &(b[n]), tnb, n - tnb); /* - */
        break;
    case -3:
    case -2:
        bn_sub_part_words(t, &(a[n]), a, tna, tna - n); /* - */
        bn_sub_part_words(&(t[n]), &(b[n]), b, tnb, tnb - n); /* + */
        neg = 1;
        break;
    case -1:
    case 0:
    case 1:
    case 2:
        bn_sub_part_words(t, a, &(a[n]), tna, n - tna); /* + */
        bn_sub_part_words(&(t[n]), b, &(b[n]), tnb, n - tnb); /* - */
        neg = 1;
        break;
    case 3:
    case 4:
        bn_sub_part_words(t, a, &(a[n]), tna, n - tna);
        bn_sub_part_words(&(t[n]), &(b[n]), b, tnb, tnb - n);
        break;
    }
    /*
     * The zero case isn't yet implemented here. The speedup would probably
     * be negligible.
     */
# if 0
    if (n == 4) {
        bn_mul_comba4(&(t[n2]), t, &(t[n]));
        bn_mul_comba4(r, a, b);
        bn_mul_normal(&(r[n2]), &(a[n]), tn, &(b[n]), tn);
        memset(&r[n2 + tn * 2], 0, sizeof(*r) * (n2 - tn * 2));
    } else
# endif
    if (n == 8) {
        bn_mul_comba8(&(t[n2]), t, &(t[n]));
        bn_mul_comba8(r, a, b);
        bn_mul_normal(&(r[n2]), &(a[n]), tna, &(b[n]), tnb);
        memset(&r[n2 + tna + tnb], 0, sizeof(*r) * (n2 - tna - tnb));
    } else {
        p = &(t[n2 * 2]);
        bn_mul_recursive(&(t[n2]), t, &(t[n]), n, 0, 0, p);
        bn_mul_recursive(r, a, b, n, 0, 0, p);
        i = n / 2;
        /*
         * If there is only a bottom half to the number, just do it
         */
        if (tna > tnb)
            j = tna - i;
        else
            j = tnb - i;
        if (j == 0) {
            bn_mul_recursive(&(r[n2]), &(a[n]), &(b[n]),
                             i, tna - i, tnb - i, p);
            memset(&r[n2 + i * 2], 0, sizeof(*r) * (n2 - i * 2));
        } else if (j > 0) {     /* eg, n == 16, i == 8 and tn == 11 */
            bn_mul_part_recursive(&(r[n2]), &(a[n]), &(b[n]),
                                  i, tna - i, tnb - i, p);
            memset(&(r[n2 + tna + tnb]), 0,
                   sizeof(BN_ULONG) * (n2 - tna - tnb));
        } else {                /* (j < 0) eg, n == 16, i == 8 and tn == 5 */

            memset(&r[n2], 0, sizeof(*r) * n2);
            if (tna < BN_MUL_RECURSIVE_SIZE_NORMAL
                && tnb < BN_MUL_RECURSIVE_SIZE_NORMAL) {
                bn_mul_normal(&(r[n2]), &(a[n]), tna, &(b[n]), tnb);
            } else {
                for (;;) {
                    i /= 2;
                    /*
                     * these simplified conditions work exclusively because
                     * difference between tna and tnb is 1 or 0
                     */
                    if (i < tna || i < tnb) {
                        bn_mul_part_recursive(&(r[n2]),
                                              &(a[n]), &(b[n]),
                                              i, tna - i, tnb - i, p);
                        break;
                    } else if (i == tna || i == tnb) {
                        bn_mul_recursive(&(r[n2]),
                                         &(a[n]), &(b[n]),
                                         i, tna - i, tnb - i, p);
                        break;
                    }
                }
            }
        }
    }

    /*-
     * t[32] holds (a[0]-a[1])*(b[1]-b[0]), c1 is the sign
     * r[10] holds (a[0]*b[0])
     * r[32] holds (b[1]*b[1])
     */

    c1 = (int)(bn_add_words(t, r, &(r[n2]), n2));

    if (neg) {                  /* if t[32] is negative */
        c1 -= (int)(bn_sub_words(&(t[n2]), t, &(t[n2]), n2));
    } else {
        /* Might have a carry */
        c1 += (int)(bn_add_words(&(t[n2]), &(t[n2]), t, n2));
    }

    /*-
     * t[32] holds (a[0]-a[1])*(b[1]-b[0])+(a[0]*b[0])+(a[1]*b[1])
     * r[10] holds (a[0]*b[0])
     * r[32] holds (b[1]*b[1])
     * c1 holds the carry bits
     */
    c1 += (int)(bn_add_words(&(r[n]), &(r[n]), &(t[n2]), n2));
    if (c1) {
        p = &(r[n + n2]);
        lo = *p;
        ln = (lo + c1) & BN_MASK2;
        *p = ln;

        /*
         * The overflow will stop before we over write words we should not
         * overwrite
         */
        if (ln < (BN_ULONG)c1) {
            do {
                p++;
                lo = *p;
                ln = (lo + 1) & BN_MASK2;
                *p = ln;
            } while (ln == 0);
        }
    }
}
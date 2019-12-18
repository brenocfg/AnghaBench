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
struct TYPE_4__ {int* d; int top; int /*<<< orphan*/  flags; } ;
typedef  int volatile BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_FIXED_TOP ; 
 int /*<<< orphan*/ * bn_wexpand (TYPE_1__*,int) ; 
 int constant_time_eq_int (int,int) ; 

__attribute__((used)) static int MOD_EXP_CTIME_COPY_FROM_PREBUF(BIGNUM *b, int top,
                                          unsigned char *buf, int idx,
                                          int window)
{
    int i, j;
    int width = 1 << window;
    /*
     * We declare table 'volatile' in order to discourage compiler
     * from reordering loads from the table. Concern is that if
     * reordered in specific manner loads might give away the
     * information we are trying to conceal. Some would argue that
     * compiler can reorder them anyway, but it can as well be
     * argued that doing so would be violation of standard...
     */
    volatile BN_ULONG *table = (volatile BN_ULONG *)buf;

    if (bn_wexpand(b, top) == NULL)
        return 0;

    if (window <= 3) {
        for (i = 0; i < top; i++, table += width) {
            BN_ULONG acc = 0;

            for (j = 0; j < width; j++) {
                acc |= table[j] &
                       ((BN_ULONG)0 - (constant_time_eq_int(j,idx)&1));
            }

            b->d[i] = acc;
        }
    } else {
        int xstride = 1 << (window - 2);
        BN_ULONG y0, y1, y2, y3;

        i = idx >> (window - 2);        /* equivalent of idx / xstride */
        idx &= xstride - 1;             /* equivalent of idx % xstride */

        y0 = (BN_ULONG)0 - (constant_time_eq_int(i,0)&1);
        y1 = (BN_ULONG)0 - (constant_time_eq_int(i,1)&1);
        y2 = (BN_ULONG)0 - (constant_time_eq_int(i,2)&1);
        y3 = (BN_ULONG)0 - (constant_time_eq_int(i,3)&1);

        for (i = 0; i < top; i++, table += width) {
            BN_ULONG acc = 0;

            for (j = 0; j < xstride; j++) {
                acc |= ( (table[j + 0 * xstride] & y0) |
                         (table[j + 1 * xstride] & y1) |
                         (table[j + 2 * xstride] & y2) |
                         (table[j + 3 * xstride] & y3) )
                       & ((BN_ULONG)0 - (constant_time_eq_int(j,idx)&1));
            }

            b->d[i] = acc;
        }
    }

    b->top = top;
    b->flags |= BN_FLG_FIXED_TOP;
    return 1;
}
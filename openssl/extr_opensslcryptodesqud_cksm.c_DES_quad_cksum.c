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
typedef  int /*<<< orphan*/ * DES_cblock ;
typedef  int DES_LONG ;

/* Variables and functions */
 int NOISE ; 
 int Q_B0 (int /*<<< orphan*/ ) ; 
 int Q_B1 (int /*<<< orphan*/ ) ; 
 int Q_B2 (int /*<<< orphan*/ ) ; 
 int Q_B3 (int /*<<< orphan*/ ) ; 

DES_LONG DES_quad_cksum(const unsigned char *input, DES_cblock output[],
                        long length, int out_count, DES_cblock *seed)
{
    DES_LONG z0, z1, t0, t1;
    int i;
    long l;
    const unsigned char *cp;
    DES_LONG *lp;

    if (out_count < 1)
        out_count = 1;
    lp = (DES_LONG *)&(output[0])[0];

    z0 = Q_B0((*seed)[0]) | Q_B1((*seed)[1]) | Q_B2((*seed)[2]) |
        Q_B3((*seed)[3]);
    z1 = Q_B0((*seed)[4]) | Q_B1((*seed)[5]) | Q_B2((*seed)[6]) |
        Q_B3((*seed)[7]);

    for (i = 0; ((i < 4) && (i < out_count)); i++) {
        cp = input;
        l = length;
        while (l > 0) {
            if (l > 1) {
                t0 = (DES_LONG)(*(cp++));
                t0 |= (DES_LONG)Q_B1(*(cp++));
                l--;
            } else
                t0 = (DES_LONG)(*(cp++));
            l--;
            /* add */
            t0 += z0;
            t0 &= 0xffffffffL;
            t1 = z1;
            /* square, well sort of square */
            z0 = ((((t0 * t0) & 0xffffffffL) + ((t1 * t1) & 0xffffffffL))
                  & 0xffffffffL) % 0x7fffffffL;
            z1 = ((t0 * ((t1 + NOISE) & 0xffffffffL)) & 0xffffffffL) %
                0x7fffffffL;
        }
        if (lp != NULL) {
            /*
             * The MIT library assumes that the checksum is composed of
             * 2*out_count 32 bit ints
             */
            *lp++ = z0;
            *lp++ = z1;
        }
    }
    return z0;
}
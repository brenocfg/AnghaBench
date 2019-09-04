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
struct TYPE_3__ {int* data; } ;
typedef  TYPE_1__ RC2_KEY ;
typedef  int RC2_INT ;

/* Variables and functions */

void RC2_decrypt(unsigned long *d, RC2_KEY *key)
{
    int i, n;
    register RC2_INT *p0, *p1;
    register RC2_INT x0, x1, x2, x3, t;
    unsigned long l;

    l = d[0];
    x0 = (RC2_INT) l & 0xffff;
    x1 = (RC2_INT) (l >> 16L);
    l = d[1];
    x2 = (RC2_INT) l & 0xffff;
    x3 = (RC2_INT) (l >> 16L);

    n = 3;
    i = 5;

    p0 = &(key->data[63]);
    p1 = &(key->data[0]);
    for (;;) {
        t = ((x3 << 11) | (x3 >> 5)) & 0xffff;
        x3 = (t - (x0 & ~x2) - (x1 & x2) - *(p0--)) & 0xffff;
        t = ((x2 << 13) | (x2 >> 3)) & 0xffff;
        x2 = (t - (x3 & ~x1) - (x0 & x1) - *(p0--)) & 0xffff;
        t = ((x1 << 14) | (x1 >> 2)) & 0xffff;
        x1 = (t - (x2 & ~x0) - (x3 & x0) - *(p0--)) & 0xffff;
        t = ((x0 << 15) | (x0 >> 1)) & 0xffff;
        x0 = (t - (x1 & ~x3) - (x2 & x3) - *(p0--)) & 0xffff;

        if (--i == 0) {
            if (--n == 0)
                break;
            i = (n == 2) ? 6 : 5;

            x3 = (x3 - p1[x2 & 0x3f]) & 0xffff;
            x2 = (x2 - p1[x1 & 0x3f]) & 0xffff;
            x1 = (x1 - p1[x0 & 0x3f]) & 0xffff;
            x0 = (x0 - p1[x3 & 0x3f]) & 0xffff;
        }
    }

    d[0] =
        (unsigned long)(x0 & 0xffff) | ((unsigned long)(x1 & 0xffff) << 16L);
    d[1] =
        (unsigned long)(x2 & 0xffff) | ((unsigned long)(x3 & 0xffff) << 16L);
}
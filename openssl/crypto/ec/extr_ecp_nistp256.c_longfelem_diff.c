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
typedef  scalar_t__* longfelem ;
typedef  int limb ;

/* Variables and functions */

__attribute__((used)) static void longfelem_diff(longfelem out, const longfelem in)
{
    static const limb two70m8p6 =
        (((limb) 1) << 70) - (((limb) 1) << 8) + (((limb) 1) << 6);
    static const limb two70p40 = (((limb) 1) << 70) + (((limb) 1) << 40);
    static const limb two70 = (((limb) 1) << 70);
    static const limb two70m40m38p6 =
        (((limb) 1) << 70) - (((limb) 1) << 40) - (((limb) 1) << 38) +
        (((limb) 1) << 6);
    static const limb two70m6 = (((limb) 1) << 70) - (((limb) 1) << 6);

    /* add 0 mod p to avoid underflow */
    out[0] += two70m8p6;
    out[1] += two70p40;
    out[2] += two70;
    out[3] += two70m40m38p6;
    out[4] += two70m6;
    out[5] += two70m6;
    out[6] += two70m6;
    out[7] += two70m6;

    /* in[i] < 7*2^67 < 2^70 - 2^40 - 2^38 + 2^6 */
    out[0] -= in[0];
    out[1] -= in[1];
    out[2] -= in[2];
    out[3] -= in[3];
    out[4] -= in[4];
    out[5] -= in[5];
    out[6] -= in[6];
    out[7] -= in[7];
}
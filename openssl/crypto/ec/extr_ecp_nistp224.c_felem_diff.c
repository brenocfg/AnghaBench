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
typedef  int limb ;
typedef  scalar_t__* felem ;

/* Variables and functions */

__attribute__((used)) static void felem_diff(felem out, const felem in)
{
    static const limb two58p2 = (((limb) 1) << 58) + (((limb) 1) << 2);
    static const limb two58m2 = (((limb) 1) << 58) - (((limb) 1) << 2);
    static const limb two58m42m2 = (((limb) 1) << 58) -
        (((limb) 1) << 42) - (((limb) 1) << 2);

    /* Add 0 mod 2^224-2^96+1 to ensure out > in */
    out[0] += two58p2;
    out[1] += two58m42m2;
    out[2] += two58m2;
    out[3] += two58m2;

    out[0] -= in[0];
    out[1] -= in[1];
    out[2] -= in[2];
    out[3] -= in[3];
}
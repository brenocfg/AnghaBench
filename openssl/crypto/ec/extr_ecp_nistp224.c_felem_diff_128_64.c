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
typedef  int widelimb ;
typedef  int /*<<< orphan*/ * widefelem ;
typedef  scalar_t__* felem ;

/* Variables and functions */

__attribute__((used)) static void felem_diff_128_64(widefelem out, const felem in)
{
    static const widelimb two64p8 = (((widelimb) 1) << 64) +
        (((widelimb) 1) << 8);
    static const widelimb two64m8 = (((widelimb) 1) << 64) -
        (((widelimb) 1) << 8);
    static const widelimb two64m48m8 = (((widelimb) 1) << 64) -
        (((widelimb) 1) << 48) - (((widelimb) 1) << 8);

    /* Add 0 mod 2^224-2^96+1 to ensure out > in */
    out[0] += two64p8;
    out[1] += two64m48m8;
    out[2] += two64m8;
    out[3] += two64m8;

    out[0] -= in[0];
    out[1] -= in[1];
    out[2] -= in[2];
    out[3] -= in[3];
}
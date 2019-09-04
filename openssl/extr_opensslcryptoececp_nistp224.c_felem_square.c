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
typedef  int* widefelem ;
typedef  int limb ;
typedef  int* felem ;

/* Variables and functions */

__attribute__((used)) static void felem_square(widefelem out, const felem in)
{
    limb tmp0, tmp1, tmp2;
    tmp0 = 2 * in[0];
    tmp1 = 2 * in[1];
    tmp2 = 2 * in[2];
    out[0] = ((widelimb) in[0]) * in[0];
    out[1] = ((widelimb) in[0]) * tmp1;
    out[2] = ((widelimb) in[0]) * tmp2 + ((widelimb) in[1]) * in[1];
    out[3] = ((widelimb) in[3]) * tmp0 + ((widelimb) in[1]) * tmp2;
    out[4] = ((widelimb) in[3]) * tmp1 + ((widelimb) in[2]) * in[2];
    out[5] = ((widelimb) in[3]) * tmp2;
    out[6] = ((widelimb) in[3]) * in[3];
}
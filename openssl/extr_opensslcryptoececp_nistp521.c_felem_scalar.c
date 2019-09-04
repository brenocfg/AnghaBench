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
typedef  int* felem ;

/* Variables and functions */

__attribute__((used)) static void felem_scalar(felem out, const felem in, limb scalar)
{
    out[0] = in[0] * scalar;
    out[1] = in[1] * scalar;
    out[2] = in[2] * scalar;
    out[3] = in[3] * scalar;
    out[4] = in[4] * scalar;
    out[5] = in[5] * scalar;
    out[6] = in[6] * scalar;
    out[7] = in[7] * scalar;
    out[8] = in[8] * scalar;
}
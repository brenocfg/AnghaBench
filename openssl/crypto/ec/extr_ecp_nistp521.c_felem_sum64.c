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
typedef  scalar_t__* felem ;

/* Variables and functions */

__attribute__((used)) static void felem_sum64(felem out, const felem in)
{
    out[0] += in[0];
    out[1] += in[1];
    out[2] += in[2];
    out[3] += in[3];
    out[4] += in[4];
    out[5] += in[5];
    out[6] += in[6];
    out[7] += in[7];
    out[8] += in[8];
}
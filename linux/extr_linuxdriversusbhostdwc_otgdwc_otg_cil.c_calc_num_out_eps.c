#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {int d32; } ;
struct TYPE_6__ {int num_dev_ep; } ;
struct TYPE_7__ {TYPE_1__ b; } ;
struct TYPE_9__ {TYPE_3__ hwcfg1; TYPE_2__ hwcfg2; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t calc_num_out_eps(dwc_otg_core_if_t * core_if)
{
	uint32_t num_out_eps = 0;
	uint32_t num_eps = core_if->hwcfg2.b.num_dev_ep;
	uint32_t hwcfg1 = core_if->hwcfg1.d32 >> 2;
	int i;

	for (i = 0; i < num_eps; ++i) {
		if (!(hwcfg1 & 0x1))
			num_out_eps++;

		hwcfg1 >>= 2;
	}
	return num_out_eps;
}
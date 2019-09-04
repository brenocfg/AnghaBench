#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {int num_in_eps; scalar_t__ ded_fifo_en; } ;
struct TYPE_11__ {TYPE_5__ b; } ;
struct TYPE_10__ {int d32; } ;
struct TYPE_8__ {int num_dev_ep; } ;
struct TYPE_9__ {TYPE_1__ b; } ;
struct TYPE_13__ {TYPE_4__ hwcfg4; TYPE_3__ hwcfg1; TYPE_2__ hwcfg2; } ;
typedef  TYPE_6__ dwc_otg_core_if_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t calc_num_in_eps(dwc_otg_core_if_t * core_if)
{
	uint32_t num_in_eps = 0;
	uint32_t num_eps = core_if->hwcfg2.b.num_dev_ep;
	uint32_t hwcfg1 = core_if->hwcfg1.d32 >> 3;
	uint32_t num_tx_fifos = core_if->hwcfg4.b.num_in_eps;
	int i;

	for (i = 0; i < num_eps; ++i) {
		if (!(hwcfg1 & 0x1))
			num_in_eps++;

		hwcfg1 >>= 2;
	}

	if (core_if->hwcfg4.b.ded_fifo_en) {
		num_in_eps =
		    (num_in_eps > num_tx_fifos) ? num_tx_fifos : num_in_eps;
	}

	return num_in_eps;
}
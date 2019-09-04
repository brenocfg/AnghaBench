#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int num_in_eps; } ;
struct TYPE_6__ {TYPE_1__ b; } ;
struct TYPE_7__ {int tx_msk; TYPE_2__ hwcfg4; } ;
typedef  TYPE_3__ dwc_otg_core_if_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t assign_tx_fifo(dwc_otg_core_if_t * core_if)
{
	uint32_t TxMsk = 1;
	int i;

	for (i = 0; i < core_if->hwcfg4.b.num_in_eps; ++i) {
		if ((TxMsk & core_if->tx_msk) == 0) {
			core_if->tx_msk |= TxMsk;
			return i + 1;
		}
		TxMsk <<= 1;
	}
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  hcint; int /*<<< orphan*/  hcintmsk; } ;
typedef  TYPE_2__ dwc_otg_hc_regs_t ;
struct TYPE_9__ {TYPE_1__* host_if; } ;
typedef  TYPE_3__ dwc_otg_core_if_t ;
struct TYPE_10__ {size_t hc_num; scalar_t__ xfer_started; } ;
typedef  TYPE_4__ dwc_hc_t ;
struct TYPE_7__ {TYPE_2__** hc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int) ; 

void dwc_otg_hc_cleanup(dwc_otg_core_if_t * core_if, dwc_hc_t * hc)
{
	dwc_otg_hc_regs_t *hc_regs;

	hc->xfer_started = 0;

	/*
	 * Clear channel interrupt enables and any unhandled channel interrupt
	 * conditions.
	 */
	hc_regs = core_if->host_if->hc_regs[hc->hc_num];
	DWC_WRITE_REG32(&hc_regs->hcintmsk, 0);
	DWC_WRITE_REG32(&hc_regs->hcint, 0xFFFFFFFF);
#ifdef DEBUG
	DWC_TIMER_CANCEL(core_if->hc_xfer_timer[hc->hc_num]);
#endif
}
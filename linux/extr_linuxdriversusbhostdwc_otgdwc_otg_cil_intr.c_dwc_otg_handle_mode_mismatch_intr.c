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
typedef  int int32_t ;
struct TYPE_7__ {int modemismatch; } ;
struct TYPE_9__ {scalar_t__ d32; TYPE_1__ b; } ;
typedef  TYPE_3__ gintsts_data_t ;
struct TYPE_10__ {TYPE_2__* core_global_regs; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_8__ {int /*<<< orphan*/  gintsts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_WARN (char*,char*) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ dwc_otg_mode (TYPE_4__*) ; 

int32_t dwc_otg_handle_mode_mismatch_intr(dwc_otg_core_if_t * core_if)
{
	gintsts_data_t gintsts;
	DWC_WARN("Mode Mismatch Interrupt: currently in %s mode\n",
		 dwc_otg_mode(core_if) ? "Host" : "Device");

	/* Clear interrupt */
	gintsts.d32 = 0;
	gintsts.b.modemismatch = 1;
	DWC_WRITE_REG32(&core_if->core_global_regs->gintsts, gintsts.d32);
	return 1;
}
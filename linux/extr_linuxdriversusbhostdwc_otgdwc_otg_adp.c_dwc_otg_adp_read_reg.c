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
typedef  scalar_t__ uint32_t ;
struct TYPE_8__ {TYPE_2__* core_global_regs; } ;
typedef  TYPE_3__ dwc_otg_core_if_t ;
struct TYPE_6__ {int ar; } ;
struct TYPE_9__ {scalar_t__ d32; TYPE_1__ b; } ;
typedef  TYPE_4__ adpctl_data_t ;
struct TYPE_7__ {int /*<<< orphan*/  adpctl; } ;

/* Variables and functions */
 scalar_t__ DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,scalar_t__) ; 

uint32_t dwc_otg_adp_read_reg(dwc_otg_core_if_t * core_if)
{
	adpctl_data_t adpctl;

	adpctl.d32 = 0;
	adpctl.b.ar = 0x1;

	DWC_WRITE_REG32(&core_if->core_global_regs->adpctl, adpctl.d32);

	while (adpctl.b.ar) {
		adpctl.d32 = DWC_READ_REG32(&core_if->core_global_regs->adpctl);
	}

	return adpctl.d32;
}
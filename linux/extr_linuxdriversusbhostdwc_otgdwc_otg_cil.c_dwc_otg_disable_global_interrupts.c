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
struct TYPE_6__ {int glblintrmsk; } ;
struct TYPE_8__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_3__ gahbcfg_data_t ;
struct TYPE_9__ {TYPE_2__* core_global_regs; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_7__ {int /*<<< orphan*/  gahbcfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dwc_otg_disable_global_interrupts(dwc_otg_core_if_t * core_if)
{
	gahbcfg_data_t ahbcfg = {.d32 = 0 };
	ahbcfg.b.glblintrmsk = 1;	/* Disable interrupts */
	DWC_MODIFY_REG32(&core_if->core_global_regs->gahbcfg, ahbcfg.d32, 0);
}
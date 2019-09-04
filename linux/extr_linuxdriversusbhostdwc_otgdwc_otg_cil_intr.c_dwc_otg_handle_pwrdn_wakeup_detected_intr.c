#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_8__ {scalar_t__ idsts; } ;
struct TYPE_10__ {TYPE_1__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_3__ gpwrdn_data_t ;
struct TYPE_11__ {int hibernation_suspend; int power_down; TYPE_2__* core_global_regs; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_9__ {int /*<<< orphan*/  gpwrdn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ANY ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DWC_PRINTF (char*) ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_device_hibernation_restore (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_host_hibernation_restore (TYPE_4__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t dwc_otg_handle_pwrdn_wakeup_detected_intr(dwc_otg_core_if_t * core_if)
{
	gpwrdn_data_t gpwrdn = {.d32 = 0 };
	DWC_DEBUGPL(DBG_ANY,
		    "++Powerdown Remote Wakeup Detected Interrupt++\n");

	if (!core_if->hibernation_suspend) {
		DWC_PRINTF("Already exited from Hibernation\n");
		return 1;
	}

	gpwrdn.d32 = DWC_READ_REG32(&core_if->core_global_regs->gpwrdn);
	if (gpwrdn.b.idsts) {	// Device Mode
		if ((core_if->power_down == 2)
		    && (core_if->hibernation_suspend == 1)) {
			dwc_otg_device_hibernation_restore(core_if, 0, 0);
		}
	} else {
		if ((core_if->power_down == 2)
		    && (core_if->hibernation_suspend == 1)) {
			dwc_otg_host_hibernation_restore(core_if, 1, 0);
		}
	}
	return 1;
}
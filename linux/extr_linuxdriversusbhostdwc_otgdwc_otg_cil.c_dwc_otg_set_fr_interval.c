#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {int frint; } ;
struct TYPE_13__ {int /*<<< orphan*/  d32; TYPE_2__ b; } ;
typedef  TYPE_5__ hfir_data_t ;
struct TYPE_14__ {TYPE_4__* host_if; TYPE_1__* core_params; } ;
typedef  TYPE_6__ dwc_otg_core_if_t ;
struct TYPE_12__ {TYPE_3__* host_global_regs; } ;
struct TYPE_11__ {int /*<<< orphan*/  hfir; } ;
struct TYPE_9__ {int /*<<< orphan*/  reload_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WARN (char*) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int calc_frame_interval (TYPE_6__*) ; 

void dwc_otg_set_fr_interval(dwc_otg_core_if_t * core_if, uint32_t val)
{
	hfir_data_t hfir;
	uint32_t fram_int;
	fram_int = calc_frame_interval(core_if);
	hfir.d32 = DWC_READ_REG32(&core_if->host_if->host_global_regs->hfir);
	if (!core_if->core_params->reload_ctl) {
		DWC_WARN("\nCannot reload HFIR register.HFIR.HFIRRldCtrl bit is"
			 "not set to 1.\nShould load driver with reload_ctl=1"
			 " module parameter\n");
		return;
	}
	switch (fram_int) {
	case 3750:
		if ((val < 3350) || (val > 4150)) {
			DWC_WARN("HFIR interval for HS core and 30 MHz"
				 "clock freq should be from 3350 to 4150\n");
			return;
		}
		break;
	case 30000:
		if ((val < 26820) || (val > 33180)) {
			DWC_WARN("HFIR interval for FS/LS core and 30 MHz"
				 "clock freq should be from 26820 to 33180\n");
			return;
		}
		break;
	case 6000:
		if ((val < 5360) || (val > 6640)) {
			DWC_WARN("HFIR interval for HS core and 48 MHz"
				 "clock freq should be from 5360 to 6640\n");
			return;
		}
		break;
	case 48000:
		if ((val < 42912) || (val > 53088)) {
			DWC_WARN("HFIR interval for FS/LS core and 48 MHz"
				 "clock freq should be from 42912 to 53088\n");
			return;
		}
		break;
	case 7500:
		if ((val < 6700) || (val > 8300)) {
			DWC_WARN("HFIR interval for HS core and 60 MHz"
				 "clock freq should be from 6700 to 8300\n");
			return;
		}
		break;
	case 60000:
		if ((val < 53640) || (val > 65536)) {
			DWC_WARN("HFIR interval for FS/LS core and 60 MHz"
				 "clock freq should be from 53640 to 65536\n");
			return;
		}
		break;
	default:
		DWC_WARN("Unknown frame interval\n");
		return;
		break;

	}
	hfir.b.frint = val;
	DWC_WRITE_REG32(&core_if->host_if->host_global_regs->hfir, hfir.d32);
}
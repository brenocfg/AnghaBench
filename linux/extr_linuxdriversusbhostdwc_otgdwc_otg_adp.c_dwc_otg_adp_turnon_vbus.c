#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int prtpwr; } ;
struct TYPE_4__ {TYPE_1__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_2__ hprt0_data_t ;
typedef  int /*<<< orphan*/  dwc_otg_core_if_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_PRINTF (char*,int) ; 
 int /*<<< orphan*/  dwc_otg_adp_vbuson_timer_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_read_hprt0 (int /*<<< orphan*/ *) ; 

void dwc_otg_adp_turnon_vbus(dwc_otg_core_if_t * core_if)
{
	hprt0_data_t hprt0 = {.d32 = 0 };
	hprt0.d32 = dwc_otg_read_hprt0(core_if);
	DWC_PRINTF("Turn on VBUS for 1.1s, port power is %d\n", hprt0.b.prtpwr);

	if (hprt0.b.prtpwr == 0) {
		hprt0.b.prtpwr = 1;
		//DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
	}

	dwc_otg_adp_vbuson_timer_start(core_if);
}
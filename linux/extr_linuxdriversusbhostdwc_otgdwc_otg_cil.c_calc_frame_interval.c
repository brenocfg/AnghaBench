#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_14__ {int fs_phy_type; } ;
struct TYPE_16__ {TYPE_4__ b; void* d32; } ;
typedef  TYPE_6__ hwcfg2_data_t ;
struct TYPE_15__ {scalar_t__ prtspd; } ;
struct TYPE_17__ {TYPE_5__ b; void* d32; } ;
typedef  TYPE_7__ hprt0_data_t ;
struct TYPE_13__ {scalar_t__ physel; scalar_t__ phyif; scalar_t__ ulpi_utmi_sel; scalar_t__ phylpwrclksel; } ;
struct TYPE_18__ {TYPE_3__ b; void* d32; } ;
typedef  TYPE_8__ gusbcfg_data_t ;
struct TYPE_19__ {TYPE_2__* host_if; TYPE_1__* core_global_regs; } ;
typedef  TYPE_9__ dwc_otg_core_if_t ;
struct TYPE_12__ {int /*<<< orphan*/ * hprt0; } ;
struct TYPE_11__ {int /*<<< orphan*/  ghwcfg2; int /*<<< orphan*/  gusbcfg; } ;

/* Variables and functions */
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 

uint32_t calc_frame_interval(dwc_otg_core_if_t * core_if)
{
	gusbcfg_data_t usbcfg;
	hwcfg2_data_t hwcfg2;
	hprt0_data_t hprt0;
	int clock = 60;		// default value
	usbcfg.d32 = DWC_READ_REG32(&core_if->core_global_regs->gusbcfg);
	hwcfg2.d32 = DWC_READ_REG32(&core_if->core_global_regs->ghwcfg2);
	hprt0.d32 = DWC_READ_REG32(core_if->host_if->hprt0);
	if (!usbcfg.b.physel && usbcfg.b.ulpi_utmi_sel && !usbcfg.b.phyif)
		clock = 60;
	if (usbcfg.b.physel && hwcfg2.b.fs_phy_type == 3)
		clock = 48;
	if (!usbcfg.b.phylpwrclksel && !usbcfg.b.physel &&
	    !usbcfg.b.ulpi_utmi_sel && usbcfg.b.phyif)
		clock = 30;
	if (!usbcfg.b.phylpwrclksel && !usbcfg.b.physel &&
	    !usbcfg.b.ulpi_utmi_sel && !usbcfg.b.phyif)
		clock = 60;
	if (usbcfg.b.phylpwrclksel && !usbcfg.b.physel &&
	    !usbcfg.b.ulpi_utmi_sel && usbcfg.b.phyif)
		clock = 48;
	if (usbcfg.b.physel && !usbcfg.b.phyif && hwcfg2.b.fs_phy_type == 2)
		clock = 48;
	if (usbcfg.b.physel && hwcfg2.b.fs_phy_type == 1)
		clock = 48;
	if (hprt0.b.prtspd == 0)
		/* High speed case */
		return 125 * clock - 1;
	else
		/* FS/LS case */
		return 1000 * clock - 1;
}
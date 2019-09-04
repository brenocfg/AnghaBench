#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int prtrst; } ;
struct TYPE_13__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_5__ hprt0_data_t ;
struct TYPE_11__ {int port_reset_change; } ;
struct TYPE_12__ {TYPE_3__ b; } ;
struct TYPE_14__ {TYPE_4__ flags; TYPE_7__* core_if; } ;
typedef  TYPE_6__ dwc_otg_hcd_t ;
struct TYPE_15__ {TYPE_2__* host_if; } ;
typedef  TYPE_7__ dwc_otg_core_if_t ;
struct TYPE_10__ {int /*<<< orphan*/  hprt0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCDV ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_mdelay (int) ; 
 int /*<<< orphan*/  dwc_otg_read_hprt0 (TYPE_7__*) ; 

__attribute__((used)) static void reset_tasklet_func(void *data)
{
	dwc_otg_hcd_t *dwc_otg_hcd = (dwc_otg_hcd_t *) data;
	dwc_otg_core_if_t *core_if = dwc_otg_hcd->core_if;
	hprt0_data_t hprt0;

	DWC_DEBUGPL(DBG_HCDV, "USB RESET tasklet called\n");

	hprt0.d32 = dwc_otg_read_hprt0(core_if);
	hprt0.b.prtrst = 1;
	DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
	dwc_mdelay(60);

	hprt0.b.prtrst = 0;
	DWC_WRITE_REG32(core_if->host_if->hprt0, hprt0.d32);
	dwc_otg_hcd->flags.b.port_reset_change = 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_16__ {int ginnakeff; } ;
struct TYPE_18__ {scalar_t__ d32; TYPE_4__ b; } ;
typedef  TYPE_6__ gintsts_data_t ;
struct TYPE_15__ {int ginnakeff; } ;
struct TYPE_19__ {int /*<<< orphan*/  d32; TYPE_3__ b; } ;
typedef  TYPE_7__ gintmsk_data_t ;
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_20__ {int num_in_eps; TYPE_2__** in_ep_regs; } ;
typedef  TYPE_8__ dwc_otg_dev_if_t ;
struct TYPE_21__ {scalar_t__ start_predict; TYPE_5__* core_global_regs; TYPE_8__* dev_if; } ;
typedef  TYPE_9__ dwc_otg_core_if_t ;
struct TYPE_13__ {int eptype; int epdis; int snak; scalar_t__ epena; } ;
struct TYPE_12__ {scalar_t__ d32; TYPE_1__ b; } ;
typedef  TYPE_10__ depctl_data_t ;
struct TYPE_17__ {int /*<<< orphan*/  gintsts; int /*<<< orphan*/  gintmsk; } ;
struct TYPE_14__ {int /*<<< orphan*/  diepctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_9__* GET_CORE_IF (int /*<<< orphan*/ *) ; 

int32_t dwc_otg_pcd_handle_in_nak_effective(dwc_otg_pcd_t * pcd)
{
	dwc_otg_dev_if_t *dev_if = GET_CORE_IF(pcd)->dev_if;
	depctl_data_t diepctl = {.d32 = 0 };
	gintmsk_data_t intr_mask = {.d32 = 0 };
	gintsts_data_t gintsts;
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);
	int i;

	DWC_DEBUGPL(DBG_PCD, "Global IN NAK Effective\n");

	/* Disable all active IN EPs */
	for (i = 0; i <= dev_if->num_in_eps; i++) {
		diepctl.d32 = DWC_READ_REG32(&dev_if->in_ep_regs[i]->diepctl);
		if (!(diepctl.b.eptype & 1) && diepctl.b.epena) {
			if (core_if->start_predict > 0)
				core_if->start_predict++;
			diepctl.b.epdis = 1;
			diepctl.b.snak = 1;
			DWC_WRITE_REG32(&dev_if->in_ep_regs[i]->diepctl, diepctl.d32);
		}
	}


	/* Disable the Global IN NAK Effective Interrupt */
	intr_mask.b.ginnakeff = 1;
	DWC_MODIFY_REG32(&GET_CORE_IF(pcd)->core_global_regs->gintmsk,
			 intr_mask.d32, 0);

	/* Clear interrupt */
	gintsts.d32 = 0;
	gintsts.b.ginnakeff = 1;
	DWC_WRITE_REG32(&GET_CORE_IF(pcd)->core_global_regs->gintsts,
			gintsts.d32);

	return 1;
}
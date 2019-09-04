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
struct TYPE_14__ {scalar_t__ queue_sof; } ;
struct TYPE_11__ {TYPE_6__* in_ep; TYPE_6__ ep0; } ;
typedef  TYPE_3__ dwc_otg_pcd_t ;
struct TYPE_12__ {TYPE_2__* dev_if; } ;
typedef  TYPE_4__ dwc_otg_core_if_t ;
struct TYPE_13__ {void* d32; } ;
typedef  TYPE_5__ depctl_data_t ;
struct TYPE_10__ {int num_in_eps; TYPE_1__** in_ep_regs; } ;
struct TYPE_9__ {int /*<<< orphan*/  diepctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCDV ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*) ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 TYPE_4__* GET_CORE_IF (TYPE_3__*) ; 
 int /*<<< orphan*/  start_next_request (TYPE_6__*) ; 

__attribute__((used)) static void start_xfer_tasklet_func(void *data)
{
	dwc_otg_pcd_t *pcd = (dwc_otg_pcd_t *) data;
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);

	int i;
	depctl_data_t diepctl;

	DWC_DEBUGPL(DBG_PCDV, "Start xfer tasklet\n");

	diepctl.d32 = DWC_READ_REG32(&core_if->dev_if->in_ep_regs[0]->diepctl);

	if (pcd->ep0.queue_sof) {
		pcd->ep0.queue_sof = 0;
		start_next_request(&pcd->ep0);
		// break;
	}

	for (i = 0; i < core_if->dev_if->num_in_eps; i++) {
		depctl_data_t diepctl;
		diepctl.d32 =
		    DWC_READ_REG32(&core_if->dev_if->in_ep_regs[i]->diepctl);

		if (pcd->in_ep[i].queue_sof) {
			pcd->in_ep[i].queue_sof = 0;
			start_next_request(&pcd->in_ep[i]);
			// break;
		}
	}

	return;
}
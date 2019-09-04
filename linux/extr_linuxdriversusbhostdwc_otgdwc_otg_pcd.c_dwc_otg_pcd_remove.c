#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct device {int dummy; } ;
struct TYPE_15__ {TYPE_3__* core_if; int /*<<< orphan*/  test_mode_tasklet; int /*<<< orphan*/  start_xfer_tasklet; int /*<<< orphan*/  lock; struct TYPE_15__* status_buf; struct TYPE_15__* setup_pkt; int /*<<< orphan*/  status_buf_dma_handle; int /*<<< orphan*/  setup_pkt_dma_handle; } ;
typedef  TYPE_4__ dwc_otg_pcd_t ;
struct TYPE_16__ {int /*<<< orphan*/  dma_out_desc_addr; int /*<<< orphan*/  out_desc_addr; int /*<<< orphan*/  dma_in_desc_addr; int /*<<< orphan*/  in_desc_addr; int /*<<< orphan*/ * dma_setup_desc_addr; int /*<<< orphan*/ * setup_desc_addr; } ;
typedef  TYPE_5__ dwc_otg_dev_if_t ;
struct TYPE_17__ {scalar_t__ dma_desc_enable; scalar_t__ dma_enable; TYPE_5__* dev_if; } ;
struct TYPE_14__ {scalar_t__* ep_xfer_timer; TYPE_2__* core_params; int /*<<< orphan*/ * lock; TYPE_1__* ep_xfer_info; } ;
struct TYPE_13__ {scalar_t__ dev_out_nak; } ;
struct TYPE_12__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_DMA_FREE (struct device*,int,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_FREE (TYPE_4__*) ; 
 int /*<<< orphan*/  DWC_SPINLOCK_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_TASK_FREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_TIMER_CANCEL (scalar_t__) ; 
 int /*<<< orphan*/  DWC_TIMER_FREE (scalar_t__) ; 
 TYPE_8__* GET_CORE_IF (TYPE_4__*) ; 
 int MAX_EPS_CHANNELS ; 
 int /*<<< orphan*/  dwc_otg_ep_free_desc_chain (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct device* dwc_otg_pcd_to_dev (TYPE_4__*) ; 

void dwc_otg_pcd_remove(dwc_otg_pcd_t * pcd)
{
	dwc_otg_dev_if_t *dev_if = GET_CORE_IF(pcd)->dev_if;
	struct device *dev = dwc_otg_pcd_to_dev(pcd);
	int i;

	if (pcd->core_if->core_params->dev_out_nak) {
		for (i = 0; i < MAX_EPS_CHANNELS; i++) {
			DWC_TIMER_CANCEL(pcd->core_if->ep_xfer_timer[i]);
			pcd->core_if->ep_xfer_info[i].state = 0;
		}
	}

	if (GET_CORE_IF(pcd)->dma_enable) {
		DWC_DMA_FREE(dev, sizeof(*pcd->setup_pkt) * 5, pcd->setup_pkt,
			     pcd->setup_pkt_dma_handle);
		DWC_DMA_FREE(dev, sizeof(uint16_t), pcd->status_buf,
			     pcd->status_buf_dma_handle);
		if (GET_CORE_IF(pcd)->dma_desc_enable) {
			dwc_otg_ep_free_desc_chain(dev,
						   dev_if->setup_desc_addr[0],
						   dev_if->dma_setup_desc_addr
						   [0], 1);
			dwc_otg_ep_free_desc_chain(dev,
						   dev_if->setup_desc_addr[1],
						   dev_if->dma_setup_desc_addr
						   [1], 1);
			dwc_otg_ep_free_desc_chain(dev,
						   dev_if->in_desc_addr,
						   dev_if->dma_in_desc_addr, 1);
			dwc_otg_ep_free_desc_chain(dev,
						   dev_if->out_desc_addr,
						   dev_if->dma_out_desc_addr,
						   1);
		}
	} else {
		DWC_FREE(pcd->setup_pkt);
		DWC_FREE(pcd->status_buf);
	}
	DWC_SPINLOCK_FREE(pcd->lock);
	/* Set core_if's lock pointer to NULL */
	pcd->core_if->lock = NULL;

	DWC_TASK_FREE(pcd->start_xfer_tasklet);
	DWC_TASK_FREE(pcd->test_mode_tasklet);
	if (pcd->core_if->core_params->dev_out_nak) {
		for (i = 0; i < MAX_EPS_CHANNELS; i++) {
			if (pcd->core_if->ep_xfer_timer[i]) {
					DWC_TIMER_FREE(pcd->core_if->ep_xfer_timer[i]);
			}
		}
	}

/* Release the CFI object's dynamic memory */
#ifdef DWC_UTE_CFI
	if (pcd->cfi->ops.release) {
		pcd->cfi->ops.release(pcd->cfi);
	}
#endif

	DWC_FREE(pcd);
}
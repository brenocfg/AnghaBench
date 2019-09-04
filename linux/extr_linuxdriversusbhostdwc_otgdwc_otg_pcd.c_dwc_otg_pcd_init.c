#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct device {int dummy; } ;
struct TYPE_31__ {struct TYPE_31__* status_buf; struct TYPE_31__* setup_pkt; TYPE_9__* core_if; void* test_mode_tasklet; void* start_xfer_tasklet; int /*<<< orphan*/  status_buf_dma_handle; int /*<<< orphan*/  setup_pkt_dma_handle; scalar_t__ data_terminated; scalar_t__ lock; } ;
typedef  TYPE_6__ dwc_otg_pcd_t ;
struct TYPE_27__ {TYPE_1__* platformdev; } ;
struct TYPE_32__ {TYPE_9__* core_if; TYPE_2__ os_dep; } ;
typedef  TYPE_7__ dwc_otg_device_t ;
struct TYPE_33__ {scalar_t__* setup_desc_addr; scalar_t__ in_desc_addr; scalar_t__ out_desc_addr; int /*<<< orphan*/ * dma_setup_desc_addr; int /*<<< orphan*/  dma_in_desc_addr; int /*<<< orphan*/  dma_out_desc_addr; int /*<<< orphan*/ * isoc_ep; } ;
typedef  TYPE_8__ dwc_otg_dev_if_t ;
struct TYPE_28__ {scalar_t__ ded_fifo_en; } ;
struct TYPE_29__ {TYPE_3__ b; } ;
struct TYPE_34__ {struct TYPE_34__* ep_xfer_info; void** ep_xfer_timer; TYPE_5__* core_params; void* srp_timer; TYPE_4__ hwcfg4; TYPE_8__* dev_if; scalar_t__ lock; } ;
typedef  TYPE_9__ dwc_otg_core_if_t ;
struct TYPE_30__ {scalar_t__ dev_out_nak; } ;
struct TYPE_26__ {struct device dev; } ;
struct TYPE_25__ {scalar_t__ dma_desc_enable; scalar_t__ dma_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCDV ; 
 void* DWC_ALLOC (int) ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,TYPE_6__*,TYPE_9__*) ; 
 void* DWC_DMA_ALLOC (struct device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_DMA_FREE (struct device*,int,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  DWC_FREE (TYPE_6__*) ; 
 int /*<<< orphan*/  DWC_PRINTF (char*) ; 
 scalar_t__ DWC_SPINLOCK_ALLOC () ; 
 void* DWC_TASK_ALLOC (char*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 void* DWC_TIMER_ALLOC (char*,int /*<<< orphan*/ ,TYPE_9__*) ; 
 TYPE_17__* GET_CORE_IF (TYPE_6__*) ; 
 int MAX_EPS_CHANNELS ; 
 int /*<<< orphan*/  do_test_mode ; 
 int /*<<< orphan*/  dwc_otg_cil_register_pcd_callbacks (TYPE_9__*,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  dwc_otg_core_dev_init (TYPE_9__*) ; 
 void* dwc_otg_ep_alloc_desc_chain (struct device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dwc_otg_ep_free_desc_chain (struct device*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dwc_otg_is_device_mode (TYPE_9__*) ; 
 int /*<<< orphan*/  dwc_otg_pcd_reinit (TYPE_6__*) ; 
 int /*<<< orphan*/  ep_xfer_timeout ; 
 int /*<<< orphan*/  pcd_callbacks ; 
 int /*<<< orphan*/  srp_timeout ; 
 int /*<<< orphan*/  start_xfer_tasklet_func ; 

dwc_otg_pcd_t *dwc_otg_pcd_init(dwc_otg_device_t *otg_dev)
{
	struct device *dev = &otg_dev->os_dep.platformdev->dev;
	dwc_otg_core_if_t *core_if = otg_dev->core_if;
	dwc_otg_pcd_t *pcd = NULL;
	dwc_otg_dev_if_t *dev_if;
	int i;

	/*
	 * Allocate PCD structure
	 */
	pcd = DWC_ALLOC(sizeof(dwc_otg_pcd_t));

	if (pcd == NULL) {
		return NULL;
	}

#if (defined(DWC_LINUX) && defined(CONFIG_DEBUG_SPINLOCK))
	DWC_SPINLOCK_ALLOC_LINUX_DEBUG(pcd->lock);
#else
	pcd->lock = DWC_SPINLOCK_ALLOC();
#endif
        DWC_DEBUGPL(DBG_HCDV, "Init of PCD %p given core_if %p\n",
                    pcd, core_if);//GRAYG
	if (!pcd->lock) {
		DWC_ERROR("Could not allocate lock for pcd");
		DWC_FREE(pcd);
		return NULL;
	}
	/* Set core_if's lock pointer to hcd->lock */
	core_if->lock = pcd->lock;
	pcd->core_if = core_if;

	dev_if = core_if->dev_if;
	dev_if->isoc_ep = NULL;

	if (core_if->hwcfg4.b.ded_fifo_en) {
		DWC_PRINTF("Dedicated Tx FIFOs mode\n");
	} else {
		DWC_PRINTF("Shared Tx FIFO mode\n");
	}

	/*
	 * Initialized the Core for Device mode here if there is nod ADP support.
	 * Otherwise it will be done later in dwc_otg_adp_start routine.
	 */
	if (dwc_otg_is_device_mode(core_if) /*&& !core_if->adp_enable*/) {
		dwc_otg_core_dev_init(core_if);
	}

	/*
	 * Register the PCD Callbacks.
	 */
	dwc_otg_cil_register_pcd_callbacks(core_if, &pcd_callbacks, pcd);

	/*
	 * Initialize the DMA buffer for SETUP packets
	 */
	if (GET_CORE_IF(pcd)->dma_enable) {
		pcd->setup_pkt =
		    DWC_DMA_ALLOC(dev, sizeof(*pcd->setup_pkt) * 5,
				  &pcd->setup_pkt_dma_handle);
		if (pcd->setup_pkt == NULL) {
			DWC_FREE(pcd);
			return NULL;
		}

		pcd->status_buf =
		    DWC_DMA_ALLOC(dev, sizeof(uint16_t),
				  &pcd->status_buf_dma_handle);
		if (pcd->status_buf == NULL) {
			DWC_DMA_FREE(dev, sizeof(*pcd->setup_pkt) * 5,
				     pcd->setup_pkt, pcd->setup_pkt_dma_handle);
			DWC_FREE(pcd);
			return NULL;
		}

		if (GET_CORE_IF(pcd)->dma_desc_enable) {
			dev_if->setup_desc_addr[0] =
			    dwc_otg_ep_alloc_desc_chain(dev,
				&dev_if->dma_setup_desc_addr[0], 1);
			dev_if->setup_desc_addr[1] =
			    dwc_otg_ep_alloc_desc_chain(dev,
				&dev_if->dma_setup_desc_addr[1], 1);
			dev_if->in_desc_addr =
			    dwc_otg_ep_alloc_desc_chain(dev,
				&dev_if->dma_in_desc_addr, 1);
			dev_if->out_desc_addr =
			    dwc_otg_ep_alloc_desc_chain(dev,
				&dev_if->dma_out_desc_addr, 1);
			pcd->data_terminated = 0;

			if (dev_if->setup_desc_addr[0] == 0
			    || dev_if->setup_desc_addr[1] == 0
			    || dev_if->in_desc_addr == 0
			    || dev_if->out_desc_addr == 0) {

				if (dev_if->out_desc_addr)
					dwc_otg_ep_free_desc_chain(dev,
					     dev_if->out_desc_addr,
					     dev_if->dma_out_desc_addr, 1);
				if (dev_if->in_desc_addr)
					dwc_otg_ep_free_desc_chain(dev,
					     dev_if->in_desc_addr,
					     dev_if->dma_in_desc_addr, 1);
				if (dev_if->setup_desc_addr[1])
					dwc_otg_ep_free_desc_chain(dev,
					     dev_if->setup_desc_addr[1],
					     dev_if->dma_setup_desc_addr[1], 1);
				if (dev_if->setup_desc_addr[0])
					dwc_otg_ep_free_desc_chain(dev,
					     dev_if->setup_desc_addr[0],
					     dev_if->dma_setup_desc_addr[0], 1);

				DWC_DMA_FREE(dev, sizeof(*pcd->setup_pkt) * 5,
					     pcd->setup_pkt,
					     pcd->setup_pkt_dma_handle);
				DWC_DMA_FREE(dev, sizeof(*pcd->status_buf),
					     pcd->status_buf,
					     pcd->status_buf_dma_handle);

				DWC_FREE(pcd);

				return NULL;
			}
		}
	} else {
		pcd->setup_pkt = DWC_ALLOC(sizeof(*pcd->setup_pkt) * 5);
		if (pcd->setup_pkt == NULL) {
			DWC_FREE(pcd);
			return NULL;
		}

		pcd->status_buf = DWC_ALLOC(sizeof(uint16_t));
		if (pcd->status_buf == NULL) {
			DWC_FREE(pcd->setup_pkt);
			DWC_FREE(pcd);
			return NULL;
		}
	}

	dwc_otg_pcd_reinit(pcd);

	/* Allocate the cfi object for the PCD */
#ifdef DWC_UTE_CFI
	pcd->cfi = DWC_ALLOC(sizeof(cfiobject_t));
	if (NULL == pcd->cfi)
		goto fail;
	if (init_cfi(pcd->cfi)) {
		CFI_INFO("%s: Failed to init the CFI object\n", __func__);
		goto fail;
	}
#endif

	/* Initialize tasklets */
	pcd->start_xfer_tasklet = DWC_TASK_ALLOC("xfer_tasklet",
						 start_xfer_tasklet_func, pcd);
	pcd->test_mode_tasklet = DWC_TASK_ALLOC("test_mode_tasklet",
						do_test_mode, pcd);

	/* Initialize SRP timer */
	core_if->srp_timer = DWC_TIMER_ALLOC("SRP TIMER", srp_timeout, core_if);

	if (core_if->core_params->dev_out_nak) {
		/**
		* Initialize xfer timeout timer. Implemented for
		* 2.93a feature "Device DDMA OUT NAK Enhancement"
		*/
		for(i = 0; i < MAX_EPS_CHANNELS; i++) {
			pcd->core_if->ep_xfer_timer[i] =
				DWC_TIMER_ALLOC("ep timer", ep_xfer_timeout,
				&pcd->core_if->ep_xfer_info[i]);
		}
	}

	return pcd;
#ifdef DWC_UTE_CFI
fail:
#endif
	if (pcd->setup_pkt)
		DWC_FREE(pcd->setup_pkt);
	if (pcd->status_buf)
		DWC_FREE(pcd->status_buf);
#ifdef DWC_UTE_CFI
	if (pcd->cfi)
		DWC_FREE(pcd->cfi);
#endif
	if (pcd)
		DWC_FREE(pcd);
	return NULL;

}
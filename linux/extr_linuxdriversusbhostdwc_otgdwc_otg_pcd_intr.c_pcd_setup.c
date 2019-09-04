#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {int bmRequestType; int bRequest; int /*<<< orphan*/  wLength; } ;
typedef  TYPE_5__ usb_device_request_t ;
struct TYPE_25__ {int stp_rollover; int is_in; } ;
struct TYPE_28__ {TYPE_4__ dwc_ep; scalar_t__ stopped; } ;
struct TYPE_27__ {int /*<<< orphan*/  ep0state; TYPE_2__* setup_pkt; TYPE_7__ ep0; } ;
typedef  TYPE_6__ dwc_otg_pcd_t ;
typedef  TYPE_7__ dwc_otg_pcd_ep_t ;
struct TYPE_29__ {TYPE_1__** out_ep_regs; } ;
typedef  TYPE_8__ dwc_otg_dev_if_t ;
struct TYPE_30__ {int dma_enable; scalar_t__ dma_desc_enable; scalar_t__ snpsid; TYPE_8__* dev_if; } ;
typedef  TYPE_9__ dwc_otg_core_if_t ;
struct TYPE_24__ {int supcnt; } ;
struct TYPE_21__ {TYPE_3__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_10__ deptsiz0_data_t ;
struct TYPE_23__ {TYPE_5__ req; } ;
struct TYPE_22__ {int /*<<< orphan*/  doeptsiz; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*) ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EP0_IN_DATA_PHASE ; 
 int /*<<< orphan*/  EP0_IN_STATUS_PHASE ; 
 int /*<<< orphan*/  EP0_OUT_DATA_PHASE ; 
 TYPE_9__* GET_CORE_IF (TYPE_6__*) ; 
 scalar_t__ OTG_CORE_REV_2_94a ; 
 scalar_t__ OTG_CORE_REV_3_00a ; 
 int UE_DIR_IN ; 
 scalar_t__ UGETW (int /*<<< orphan*/ ) ; 
#define  UR_CLEAR_FEATURE 134 
#define  UR_GET_STATUS 133 
#define  UR_SET_ADDRESS 132 
#define  UR_SET_CONFIG 131 
#define  UR_SET_FEATURE 130 
#define  UR_SET_INTERFACE 129 
#define  UR_SYNCH_FRAME 128 
 scalar_t__ UT_GET_TYPE (int) ; 
 scalar_t__ UT_STANDARD ; 
 int /*<<< orphan*/  do_clear_feature (TYPE_6__*) ; 
 int /*<<< orphan*/  do_gadget_setup (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  do_get_status (TYPE_6__*) ; 
 int /*<<< orphan*/  do_set_address (TYPE_6__*) ; 
 int /*<<< orphan*/  do_set_feature (TYPE_6__*) ; 
 int /*<<< orphan*/  dwc_otg_request_nuke (TYPE_7__*) ; 

__attribute__((used)) static inline void pcd_setup(dwc_otg_pcd_t * pcd)
{
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);
	dwc_otg_dev_if_t *dev_if = core_if->dev_if;
	usb_device_request_t ctrl = pcd->setup_pkt->req;
	dwc_otg_pcd_ep_t *ep0 = &pcd->ep0;

	deptsiz0_data_t doeptsize0 = {.d32 = 0 };

#ifdef DWC_UTE_CFI
	int retval = 0;
	struct cfi_usb_ctrlrequest cfi_req;
#endif

	doeptsize0.d32 = DWC_READ_REG32(&dev_if->out_ep_regs[0]->doeptsiz);

	/** In BDMA more then 1 setup packet is not supported till 3.00a */
	if (core_if->dma_enable && core_if->dma_desc_enable == 0
	    && (doeptsize0.b.supcnt < 2)
	    && (core_if->snpsid < OTG_CORE_REV_2_94a)) {
		DWC_ERROR
		    ("\n\n-----------	 CANNOT handle > 1 setup packet in DMA mode\n\n");
	}
	if ((core_if->snpsid >= OTG_CORE_REV_3_00a)
	    && (core_if->dma_enable == 1) && (core_if->dma_desc_enable == 0)) {
		ctrl =
		    (pcd->setup_pkt +
		     (3 - doeptsize0.b.supcnt - 1 +
		      ep0->dwc_ep.stp_rollover))->req;
	}
#ifdef DEBUG_EP0
	DWC_DEBUGPL(DBG_PCD, "SETUP %02x.%02x v%04x i%04x l%04x\n",
		    ctrl.bmRequestType, ctrl.bRequest,
		    UGETW(ctrl.wValue), UGETW(ctrl.wIndex),
		    UGETW(ctrl.wLength));
#endif

	/* Clean up the request queue */
	dwc_otg_request_nuke(ep0);
	ep0->stopped = 0;

	if (ctrl.bmRequestType & UE_DIR_IN) {
		ep0->dwc_ep.is_in = 1;
		pcd->ep0state = EP0_IN_DATA_PHASE;
	} else {
		ep0->dwc_ep.is_in = 0;
		pcd->ep0state = EP0_OUT_DATA_PHASE;
	}

	if (UGETW(ctrl.wLength) == 0) {
		ep0->dwc_ep.is_in = 1;
		pcd->ep0state = EP0_IN_STATUS_PHASE;
	}

	if (UT_GET_TYPE(ctrl.bmRequestType) != UT_STANDARD) {

#ifdef DWC_UTE_CFI
		DWC_MEMCPY(&cfi_req, &ctrl, sizeof(usb_device_request_t));

		//printk(KERN_ALERT "CFI: req_type=0x%02x; req=0x%02x\n",
				ctrl.bRequestType, ctrl.bRequest);
		if (UT_GET_TYPE(cfi_req.bRequestType) == UT_VENDOR) {
			if (cfi_req.bRequest > 0xB0 && cfi_req.bRequest < 0xBF) {
				retval = cfi_setup(pcd, &cfi_req);
				if (retval < 0) {
					ep0_do_stall(pcd, retval);
					pcd->ep0_pending = 0;
					return;
				}

				/* if need gadget setup then call it and check the retval */
				if (pcd->cfi->need_gadget_att) {
					retval =
					    cfi_gadget_setup(pcd,
							     &pcd->
							     cfi->ctrl_req);
					if (retval < 0) {
						pcd->ep0_pending = 0;
						return;
					}
				}

				if (pcd->cfi->need_status_in_complete) {
					do_setup_in_status_phase(pcd);
				}
				return;
			}
		}
#endif

		/* handle non-standard (class/vendor) requests in the gadget driver */
		do_gadget_setup(pcd, &ctrl);
		return;
	}

	/** @todo NGS: Handle bad setup packet? */

///////////////////////////////////////////
//// --- Standard Request handling --- ////

	switch (ctrl.bRequest) {
	case UR_GET_STATUS:
		do_get_status(pcd);
		break;

	case UR_CLEAR_FEATURE:
		do_clear_feature(pcd);
		break;

	case UR_SET_FEATURE:
		do_set_feature(pcd);
		break;

	case UR_SET_ADDRESS:
		do_set_address(pcd);
		break;

	case UR_SET_INTERFACE:
	case UR_SET_CONFIG:
//              _pcd->request_config = 1;       /* Configuration changed */
		do_gadget_setup(pcd, &ctrl);
		break;

	case UR_SYNCH_FRAME:
		do_gadget_setup(pcd, &ctrl);
		break;

	default:
		/* Call the Gadget Driver's setup functions */
		do_gadget_setup(pcd, &ctrl);
		break;
	}
}
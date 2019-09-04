#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_19__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int int32_t ;
struct TYPE_24__ {void* d32; } ;
typedef  TYPE_2__ hctsiz_data_t ;
struct TYPE_25__ {void* d32; } ;
typedef  TYPE_3__ hcsplt_data_t ;
struct TYPE_26__ {void* d32; } ;
typedef  TYPE_4__ hcchar_data_t ;
struct TYPE_27__ {TYPE_6__* urb; } ;
typedef  TYPE_5__ dwc_otg_qtd_t ;
struct TYPE_28__ {char* length; char* interval; int /*<<< orphan*/  priv; scalar_t__ setup_dma; int /*<<< orphan*/  setup_packet; scalar_t__ dma; int /*<<< orphan*/  buf; int /*<<< orphan*/  pipe_info; } ;
typedef  TYPE_6__ dwc_otg_hcd_urb_t ;
struct TYPE_29__ {TYPE_19__* core_if; TYPE_1__* fops; } ;
typedef  TYPE_7__ dwc_otg_hcd_t ;
struct TYPE_30__ {int /*<<< orphan*/  hcdma; int /*<<< orphan*/  hctsiz; int /*<<< orphan*/  hcsplt; int /*<<< orphan*/  hcchar; } ;
typedef  TYPE_8__ dwc_otg_hc_regs_t ;
struct TYPE_31__ {char* hc_num; int speed; } ;
typedef  TYPE_9__ dwc_hc_t ;
struct TYPE_23__ {int /*<<< orphan*/  (* complete ) (TYPE_7__*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_22__ {scalar_t__ dma_desc_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCD ; 
 int /*<<< orphan*/  DBG_HCDI ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DWC_ERROR (char*,char*,...) ; 
 int /*<<< orphan*/  DWC_E_IO ; 
#define  DWC_OTG_EP_SPEED_FULL 134 
#define  DWC_OTG_EP_SPEED_HIGH 133 
#define  DWC_OTG_EP_SPEED_LOW 132 
 int /*<<< orphan*/  DWC_OTG_HC_XFER_AHB_ERR ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
#define  UE_BULK 131 
#define  UE_CONTROL 130 
#define  UE_INTERRUPT 129 
#define  UE_ISOCHRONOUS 128 
 int /*<<< orphan*/  ahberr ; 
 int /*<<< orphan*/  disable_hc_int (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hc_halt (TYPE_19__*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_hcd_complete_xfer_ddma (TYPE_7__*,TYPE_9__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 char* dwc_otg_hcd_get_dev_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_hcd_get_ep_num (int /*<<< orphan*/ *) ; 
 char* dwc_otg_hcd_get_mps (int /*<<< orphan*/ *) ; 
 int dwc_otg_hcd_get_pipe_type (int /*<<< orphan*/ *) ; 
 scalar_t__ dwc_otg_hcd_is_pipe_in (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t handle_hc_ahberr_intr(dwc_otg_hcd_t * hcd,
				     dwc_hc_t * hc,
				     dwc_otg_hc_regs_t * hc_regs,
				     dwc_otg_qtd_t * qtd)
{
	hcchar_data_t hcchar;
	hcsplt_data_t hcsplt;
	hctsiz_data_t hctsiz;
	uint32_t hcdma;
	char *pipetype, *speed;

	dwc_otg_hcd_urb_t *urb = qtd->urb;

	DWC_DEBUGPL(DBG_HCDI, "--Host Channel %d Interrupt: "
		    "AHB Error--\n", hc->hc_num);

	hcchar.d32 = DWC_READ_REG32(&hc_regs->hcchar);
	hcsplt.d32 = DWC_READ_REG32(&hc_regs->hcsplt);
	hctsiz.d32 = DWC_READ_REG32(&hc_regs->hctsiz);
	hcdma = DWC_READ_REG32(&hc_regs->hcdma);

	DWC_ERROR("AHB ERROR, Channel %d\n", hc->hc_num);
	DWC_ERROR("  hcchar 0x%08x, hcsplt 0x%08x\n", hcchar.d32, hcsplt.d32);
	DWC_ERROR("  hctsiz 0x%08x, hcdma 0x%08x\n", hctsiz.d32, hcdma);
	DWC_DEBUGPL(DBG_HCD, "DWC OTG HCD URB Enqueue\n");
	DWC_ERROR("  Device address: %d\n",
		  dwc_otg_hcd_get_dev_addr(&urb->pipe_info));
	DWC_ERROR("  Endpoint: %d, %s\n",
		  dwc_otg_hcd_get_ep_num(&urb->pipe_info),
		  (dwc_otg_hcd_is_pipe_in(&urb->pipe_info) ? "IN" : "OUT"));

	switch (dwc_otg_hcd_get_pipe_type(&urb->pipe_info)) {
	case UE_CONTROL:
		pipetype = "CONTROL";
		break;
	case UE_BULK:
		pipetype = "BULK";
		break;
	case UE_INTERRUPT:
		pipetype = "INTERRUPT";
		break;
	case UE_ISOCHRONOUS:
		pipetype = "ISOCHRONOUS";
		break;
	default:
		pipetype = "UNKNOWN";
		break;
	}

	DWC_ERROR("  Endpoint type: %s\n", pipetype);

	switch (hc->speed) {
	case DWC_OTG_EP_SPEED_HIGH:
		speed = "HIGH";
		break;
	case DWC_OTG_EP_SPEED_FULL:
		speed = "FULL";
		break;
	case DWC_OTG_EP_SPEED_LOW:
		speed = "LOW";
		break;
	default:
		speed = "UNKNOWN";
		break;
	};

	DWC_ERROR("  Speed: %s\n", speed);

	DWC_ERROR("  Max packet size: %d\n",
		  dwc_otg_hcd_get_mps(&urb->pipe_info));
	DWC_ERROR("  Data buffer length: %d\n", urb->length);
	DWC_ERROR("  Transfer buffer: %p, Transfer DMA: %p\n",
		  urb->buf, (void *)urb->dma);
	DWC_ERROR("  Setup buffer: %p, Setup DMA: %p\n",
		  urb->setup_packet, (void *)urb->setup_dma);
	DWC_ERROR("  Interval: %d\n", urb->interval);

	/* Core haltes the channel for Descriptor DMA mode */
	if (hcd->core_if->dma_desc_enable) {
		dwc_otg_hcd_complete_xfer_ddma(hcd, hc, hc_regs,
					       DWC_OTG_HC_XFER_AHB_ERR);
		goto handle_ahberr_done;
	}

	hcd->fops->complete(hcd, urb->priv, urb, -DWC_E_IO);

	/*
	 * Force a channel halt. Don't call halt_channel because that won't
	 * write to the HCCHARn register in DMA mode to force the halt.
	 */
	dwc_otg_hc_halt(hcd->core_if, hc, DWC_OTG_HC_XFER_AHB_ERR);
handle_ahberr_done:
	disable_hc_int(hc_regs, ahberr);
	return 1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct dwc2_hw_params {int snpsid; int dev_ep_dirs; int op_mode; int arch; int enable_dynamic_fifo; int host_channels; int hs_phy_type; int fs_phy_type; int num_dev_ep; int nperio_tx_q_depth; int host_perio_tx_q_depth; int dev_token_q_depth; int max_transfer_size; int max_packet_count; int i2c_enable; int total_fifo_size; int lpm_mode; int en_multiple_tx_fifo; int num_dev_perio_in_ep; int num_dev_in_eps; int dma_desc_enable; int power_optimized; int hibernation; int utmi_phy_data_width; int acg_enable; int ipg_isoc_en; int rx_fifo_size; } ;
struct dwc2_hsotg {int /*<<< orphan*/  dev; struct dwc2_hw_params hw_params; } ;

/* Variables and functions */
 int DWC2_FS_IOT_ID ; 
 int DWC2_HS_IOT_ID ; 
 int DWC2_OTG_ID ; 
 int ENODEV ; 
 int /*<<< orphan*/  GHWCFG1 ; 
 int /*<<< orphan*/  GHWCFG2 ; 
 int GHWCFG2_ARCHITECTURE_MASK ; 
 int GHWCFG2_ARCHITECTURE_SHIFT ; 
 int GHWCFG2_DEV_TOKEN_Q_DEPTH_MASK ; 
 int GHWCFG2_DEV_TOKEN_Q_DEPTH_SHIFT ; 
 int GHWCFG2_DYNAMIC_FIFO ; 
 int GHWCFG2_FS_PHY_TYPE_MASK ; 
 int GHWCFG2_FS_PHY_TYPE_SHIFT ; 
 int GHWCFG2_HOST_PERIO_TX_Q_DEPTH_MASK ; 
 int GHWCFG2_HOST_PERIO_TX_Q_DEPTH_SHIFT ; 
 int GHWCFG2_HS_PHY_TYPE_MASK ; 
 int GHWCFG2_HS_PHY_TYPE_SHIFT ; 
 int GHWCFG2_NONPERIO_TX_Q_DEPTH_MASK ; 
 int GHWCFG2_NONPERIO_TX_Q_DEPTH_SHIFT ; 
 int GHWCFG2_NUM_DEV_EP_MASK ; 
 int GHWCFG2_NUM_DEV_EP_SHIFT ; 
 int GHWCFG2_NUM_HOST_CHAN_MASK ; 
 int GHWCFG2_NUM_HOST_CHAN_SHIFT ; 
 int GHWCFG2_OP_MODE_MASK ; 
 int GHWCFG2_OP_MODE_SHIFT ; 
 int /*<<< orphan*/  GHWCFG3 ; 
 int GHWCFG3_DFIFO_DEPTH_MASK ; 
 int GHWCFG3_DFIFO_DEPTH_SHIFT ; 
 int GHWCFG3_I2C ; 
 int GHWCFG3_OTG_LPM_EN ; 
 int GHWCFG3_PACKET_SIZE_CNTR_WIDTH_MASK ; 
 int GHWCFG3_PACKET_SIZE_CNTR_WIDTH_SHIFT ; 
 int GHWCFG3_XFER_SIZE_CNTR_WIDTH_MASK ; 
 int GHWCFG3_XFER_SIZE_CNTR_WIDTH_SHIFT ; 
 int /*<<< orphan*/  GHWCFG4 ; 
 int GHWCFG4_ACG_SUPPORTED ; 
 int GHWCFG4_DED_FIFO_EN ; 
 int GHWCFG4_DESC_DMA ; 
 int GHWCFG4_HIBER ; 
 int GHWCFG4_IPG_ISOC_SUPPORTED ; 
 int GHWCFG4_NUM_DEV_PERIO_IN_EP_MASK ; 
 int GHWCFG4_NUM_DEV_PERIO_IN_EP_SHIFT ; 
 int GHWCFG4_NUM_IN_EPS_MASK ; 
 int GHWCFG4_NUM_IN_EPS_SHIFT ; 
 int GHWCFG4_POWER_OPTIMIZ ; 
 int GHWCFG4_UTMI_PHY_DATA_WIDTH_MASK ; 
 int GHWCFG4_UTMI_PHY_DATA_WIDTH_SHIFT ; 
 int /*<<< orphan*/  GRXFSIZ ; 
 int GRXFSIZ_DEPTH_MASK ; 
 int GRXFSIZ_DEPTH_SHIFT ; 
 int /*<<< orphan*/  GSNPSID ; 
 int GSNPSID_ID_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dwc2_get_dev_hwparams (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_get_host_hwparams (struct dwc2_hsotg*) ; 
 void* dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 

int dwc2_get_hwparams(struct dwc2_hsotg *hsotg)
{
	struct dwc2_hw_params *hw = &hsotg->hw_params;
	unsigned int width;
	u32 hwcfg1, hwcfg2, hwcfg3, hwcfg4;
	u32 grxfsiz;

	/*
	 * Attempt to ensure this device is really a DWC_otg Controller.
	 * Read and verify the GSNPSID register contents. The value should be
	 * 0x45f4xxxx, 0x5531xxxx or 0x5532xxxx
	 */

	hw->snpsid = dwc2_readl(hsotg, GSNPSID);
	if ((hw->snpsid & GSNPSID_ID_MASK) != DWC2_OTG_ID &&
	    (hw->snpsid & GSNPSID_ID_MASK) != DWC2_FS_IOT_ID &&
	    (hw->snpsid & GSNPSID_ID_MASK) != DWC2_HS_IOT_ID) {
		dev_err(hsotg->dev, "Bad value for GSNPSID: 0x%08x\n",
			hw->snpsid);
		return -ENODEV;
	}

	dev_dbg(hsotg->dev, "Core Release: %1x.%1x%1x%1x (snpsid=%x)\n",
		hw->snpsid >> 12 & 0xf, hw->snpsid >> 8 & 0xf,
		hw->snpsid >> 4 & 0xf, hw->snpsid & 0xf, hw->snpsid);

	hwcfg1 = dwc2_readl(hsotg, GHWCFG1);
	hwcfg2 = dwc2_readl(hsotg, GHWCFG2);
	hwcfg3 = dwc2_readl(hsotg, GHWCFG3);
	hwcfg4 = dwc2_readl(hsotg, GHWCFG4);
	grxfsiz = dwc2_readl(hsotg, GRXFSIZ);

	/* hwcfg1 */
	hw->dev_ep_dirs = hwcfg1;

	/* hwcfg2 */
	hw->op_mode = (hwcfg2 & GHWCFG2_OP_MODE_MASK) >>
		      GHWCFG2_OP_MODE_SHIFT;
	hw->arch = (hwcfg2 & GHWCFG2_ARCHITECTURE_MASK) >>
		   GHWCFG2_ARCHITECTURE_SHIFT;
	hw->enable_dynamic_fifo = !!(hwcfg2 & GHWCFG2_DYNAMIC_FIFO);
	hw->host_channels = 1 + ((hwcfg2 & GHWCFG2_NUM_HOST_CHAN_MASK) >>
				GHWCFG2_NUM_HOST_CHAN_SHIFT);
	hw->hs_phy_type = (hwcfg2 & GHWCFG2_HS_PHY_TYPE_MASK) >>
			  GHWCFG2_HS_PHY_TYPE_SHIFT;
	hw->fs_phy_type = (hwcfg2 & GHWCFG2_FS_PHY_TYPE_MASK) >>
			  GHWCFG2_FS_PHY_TYPE_SHIFT;
	hw->num_dev_ep = (hwcfg2 & GHWCFG2_NUM_DEV_EP_MASK) >>
			 GHWCFG2_NUM_DEV_EP_SHIFT;
	hw->nperio_tx_q_depth =
		(hwcfg2 & GHWCFG2_NONPERIO_TX_Q_DEPTH_MASK) >>
		GHWCFG2_NONPERIO_TX_Q_DEPTH_SHIFT << 1;
	hw->host_perio_tx_q_depth =
		(hwcfg2 & GHWCFG2_HOST_PERIO_TX_Q_DEPTH_MASK) >>
		GHWCFG2_HOST_PERIO_TX_Q_DEPTH_SHIFT << 1;
	hw->dev_token_q_depth =
		(hwcfg2 & GHWCFG2_DEV_TOKEN_Q_DEPTH_MASK) >>
		GHWCFG2_DEV_TOKEN_Q_DEPTH_SHIFT;

	/* hwcfg3 */
	width = (hwcfg3 & GHWCFG3_XFER_SIZE_CNTR_WIDTH_MASK) >>
		GHWCFG3_XFER_SIZE_CNTR_WIDTH_SHIFT;
	hw->max_transfer_size = (1 << (width + 11)) - 1;
	width = (hwcfg3 & GHWCFG3_PACKET_SIZE_CNTR_WIDTH_MASK) >>
		GHWCFG3_PACKET_SIZE_CNTR_WIDTH_SHIFT;
	hw->max_packet_count = (1 << (width + 4)) - 1;
	hw->i2c_enable = !!(hwcfg3 & GHWCFG3_I2C);
	hw->total_fifo_size = (hwcfg3 & GHWCFG3_DFIFO_DEPTH_MASK) >>
			      GHWCFG3_DFIFO_DEPTH_SHIFT;
	hw->lpm_mode = !!(hwcfg3 & GHWCFG3_OTG_LPM_EN);

	/* hwcfg4 */
	hw->en_multiple_tx_fifo = !!(hwcfg4 & GHWCFG4_DED_FIFO_EN);
	hw->num_dev_perio_in_ep = (hwcfg4 & GHWCFG4_NUM_DEV_PERIO_IN_EP_MASK) >>
				  GHWCFG4_NUM_DEV_PERIO_IN_EP_SHIFT;
	hw->num_dev_in_eps = (hwcfg4 & GHWCFG4_NUM_IN_EPS_MASK) >>
			     GHWCFG4_NUM_IN_EPS_SHIFT;
	hw->dma_desc_enable = !!(hwcfg4 & GHWCFG4_DESC_DMA);
	hw->power_optimized = !!(hwcfg4 & GHWCFG4_POWER_OPTIMIZ);
	hw->hibernation = !!(hwcfg4 & GHWCFG4_HIBER);
	hw->utmi_phy_data_width = (hwcfg4 & GHWCFG4_UTMI_PHY_DATA_WIDTH_MASK) >>
				  GHWCFG4_UTMI_PHY_DATA_WIDTH_SHIFT;
	hw->acg_enable = !!(hwcfg4 & GHWCFG4_ACG_SUPPORTED);
	hw->ipg_isoc_en = !!(hwcfg4 & GHWCFG4_IPG_ISOC_SUPPORTED);

	/* fifo sizes */
	hw->rx_fifo_size = (grxfsiz & GRXFSIZ_DEPTH_MASK) >>
				GRXFSIZ_DEPTH_SHIFT;
	/*
	 * Host specific hardware parameters. Reading these parameters
	 * requires the controller to be in host mode. The mode will
	 * be forced, if necessary, to read these values.
	 */
	dwc2_get_host_hwparams(hsotg);
	dwc2_get_dev_hwparams(hsotg);

	return 0;
}
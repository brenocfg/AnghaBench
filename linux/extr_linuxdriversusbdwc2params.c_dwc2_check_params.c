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
struct dwc2_hw_params {scalar_t__ arch; int enable_dynamic_fifo; int en_multiple_tx_fifo; int i2c_enable; int ipg_isoc_en; int acg_enable; scalar_t__ snpsid; int lpm_mode; int max_packet_count; int max_transfer_size; int host_channels; int rx_fifo_size; int host_nperio_tx_fifo_size; int host_perio_tx_fifo_size; int dev_nperio_tx_fifo_size; scalar_t__ dma_desc_enable; } ;
struct dwc2_core_params {int lpm; int host_dma; int dma_desc_enable; scalar_t__ phy_type; scalar_t__ g_dma; scalar_t__ besl; } ;
struct dwc2_hsotg {scalar_t__ dr_mode; struct dwc2_core_params params; struct dwc2_hw_params hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_BOOL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CHECK_RANGE (int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ DWC2_CORE_REV_2_80a ; 
 scalar_t__ DWC2_CORE_REV_2_92a ; 
 scalar_t__ DWC2_CORE_REV_3_00a ; 
 scalar_t__ DWC2_PHY_TYPE_PARAM_FS ; 
 scalar_t__ GHWCFG2_SLAVE_ONLY_ARCH ; 
 scalar_t__ USB_DR_MODE_HOST ; 
 scalar_t__ USB_DR_MODE_OTG ; 
 scalar_t__ USB_DR_MODE_PERIPHERAL ; 
 int /*<<< orphan*/  acg_enable ; 
 int /*<<< orphan*/  besl ; 
 int /*<<< orphan*/  dma_desc_enable ; 
 int /*<<< orphan*/  dma_desc_fs_enable ; 
 int /*<<< orphan*/  dwc2_check_param_otg_cap (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_check_param_phy_type (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_check_param_phy_utmi_width (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_check_param_power_down (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_check_param_speed (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_check_param_tx_fifo_sizes (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  en_multiple_tx_fifo ; 
 int /*<<< orphan*/  enable_dynamic_fifo ; 
 int /*<<< orphan*/  g_dma ; 
 int /*<<< orphan*/  g_dma_desc ; 
 int /*<<< orphan*/  g_np_tx_fifo_size ; 
 int /*<<< orphan*/  g_rx_fifo_size ; 
 int /*<<< orphan*/  hird_threshold ; 
 int /*<<< orphan*/  hird_threshold_en ; 
 int /*<<< orphan*/  host_channels ; 
 int /*<<< orphan*/  host_dma ; 
 int /*<<< orphan*/  host_ls_low_power_phy_clk ; 
 int /*<<< orphan*/  host_nperio_tx_fifo_size ; 
 int /*<<< orphan*/  host_perio_tx_fifo_size ; 
 int /*<<< orphan*/  host_rx_fifo_size ; 
 int /*<<< orphan*/  i2c_enable ; 
 int /*<<< orphan*/  ipg_isoc_en ; 
 int /*<<< orphan*/  lpm ; 
 int /*<<< orphan*/  lpm_clock_gating ; 
 int /*<<< orphan*/  max_packet_count ; 
 int /*<<< orphan*/  max_transfer_size ; 
 int /*<<< orphan*/  reload_ctl ; 

__attribute__((used)) static void dwc2_check_params(struct dwc2_hsotg *hsotg)
{
	struct dwc2_hw_params *hw = &hsotg->hw_params;
	struct dwc2_core_params *p = &hsotg->params;
	bool dma_capable = !(hw->arch == GHWCFG2_SLAVE_ONLY_ARCH);

	dwc2_check_param_otg_cap(hsotg);
	dwc2_check_param_phy_type(hsotg);
	dwc2_check_param_speed(hsotg);
	dwc2_check_param_phy_utmi_width(hsotg);
	dwc2_check_param_power_down(hsotg);
	CHECK_BOOL(enable_dynamic_fifo, hw->enable_dynamic_fifo);
	CHECK_BOOL(en_multiple_tx_fifo, hw->en_multiple_tx_fifo);
	CHECK_BOOL(i2c_enable, hw->i2c_enable);
	CHECK_BOOL(ipg_isoc_en, hw->ipg_isoc_en);
	CHECK_BOOL(acg_enable, hw->acg_enable);
	CHECK_BOOL(reload_ctl, (hsotg->hw_params.snpsid > DWC2_CORE_REV_2_92a));
	CHECK_BOOL(lpm, (hsotg->hw_params.snpsid >= DWC2_CORE_REV_2_80a));
	CHECK_BOOL(lpm, hw->lpm_mode);
	CHECK_BOOL(lpm_clock_gating, hsotg->params.lpm);
	CHECK_BOOL(besl, hsotg->params.lpm);
	CHECK_BOOL(besl, (hsotg->hw_params.snpsid >= DWC2_CORE_REV_3_00a));
	CHECK_BOOL(hird_threshold_en, hsotg->params.lpm);
	CHECK_RANGE(hird_threshold, 0, hsotg->params.besl ? 12 : 7, 0);
	CHECK_RANGE(max_packet_count,
		    15, hw->max_packet_count,
		    hw->max_packet_count);
	CHECK_RANGE(max_transfer_size,
		    2047, hw->max_transfer_size,
		    hw->max_transfer_size);

	if ((hsotg->dr_mode == USB_DR_MODE_HOST) ||
	    (hsotg->dr_mode == USB_DR_MODE_OTG)) {
		CHECK_BOOL(host_dma, dma_capable);
		CHECK_BOOL(dma_desc_enable, p->host_dma);
		CHECK_BOOL(dma_desc_fs_enable, p->dma_desc_enable);
		CHECK_BOOL(host_ls_low_power_phy_clk,
			   p->phy_type == DWC2_PHY_TYPE_PARAM_FS);
		CHECK_RANGE(host_channels,
			    1, hw->host_channels,
			    hw->host_channels);
		CHECK_RANGE(host_rx_fifo_size,
			    16, hw->rx_fifo_size,
			    hw->rx_fifo_size);
		CHECK_RANGE(host_nperio_tx_fifo_size,
			    16, hw->host_nperio_tx_fifo_size,
			    hw->host_nperio_tx_fifo_size);
		CHECK_RANGE(host_perio_tx_fifo_size,
			    16, hw->host_perio_tx_fifo_size,
			    hw->host_perio_tx_fifo_size);
	}

	if ((hsotg->dr_mode == USB_DR_MODE_PERIPHERAL) ||
	    (hsotg->dr_mode == USB_DR_MODE_OTG)) {
		CHECK_BOOL(g_dma, dma_capable);
		CHECK_BOOL(g_dma_desc, (p->g_dma && hw->dma_desc_enable));
		CHECK_RANGE(g_rx_fifo_size,
			    16, hw->rx_fifo_size,
			    hw->rx_fifo_size);
		CHECK_RANGE(g_np_tx_fifo_size,
			    16, hw->dev_nperio_tx_fifo_size,
			    hw->dev_nperio_tx_fifo_size);
		dwc2_check_param_tx_fifo_sizes(hsotg);
	}
}
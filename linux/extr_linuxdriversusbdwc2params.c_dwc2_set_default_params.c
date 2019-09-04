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
struct dwc2_hw_params {scalar_t__ arch; scalar_t__ snpsid; int /*<<< orphan*/  dma_desc_enable; int /*<<< orphan*/  host_perio_tx_fifo_size; int /*<<< orphan*/  host_nperio_tx_fifo_size; int /*<<< orphan*/  rx_fifo_size; int /*<<< orphan*/  host_channels; int /*<<< orphan*/  max_transfer_size; int /*<<< orphan*/  max_packet_count; int /*<<< orphan*/  acg_enable; int /*<<< orphan*/  i2c_enable; int /*<<< orphan*/  en_multiple_tx_fifo; int /*<<< orphan*/  enable_dynamic_fifo; } ;
struct dwc2_core_params {int phy_ulpi_ddr; int phy_ulpi_ext_vbus; int ulpi_fs_ls; int ts_dline; int reload_ctl; int uframe_sched; int external_id_pin_ctl; int lpm; int lpm_clock_gating; int besl; int hird_threshold_en; int hird_threshold; int ipg_isoc_en; int ahbcfg; int host_dma; int dma_desc_enable; int dma_desc_fs_enable; int host_support_fs_ls_low_power; int host_ls_low_power_phy_clk; int g_dma; int g_rx_fifo_size; int g_np_tx_fifo_size; int /*<<< orphan*/  g_dma_desc; int /*<<< orphan*/  host_perio_tx_fifo_size; int /*<<< orphan*/  host_nperio_tx_fifo_size; int /*<<< orphan*/  host_rx_fifo_size; int /*<<< orphan*/  host_channels; int /*<<< orphan*/  max_transfer_size; int /*<<< orphan*/  max_packet_count; int /*<<< orphan*/  acg_enable; int /*<<< orphan*/  i2c_enable; int /*<<< orphan*/  en_multiple_tx_fifo; int /*<<< orphan*/  enable_dynamic_fifo; } ;
struct dwc2_hsotg {scalar_t__ dr_mode; struct dwc2_core_params params; struct dwc2_hw_params hw_params; } ;

/* Variables and functions */
 scalar_t__ DWC2_CORE_REV_2_92a ; 
 int GAHBCFG_HBSTLEN_INCR ; 
 int GAHBCFG_HBSTLEN_SHIFT ; 
 scalar_t__ GHWCFG2_SLAVE_ONLY_ARCH ; 
 scalar_t__ USB_DR_MODE_HOST ; 
 scalar_t__ USB_DR_MODE_OTG ; 
 scalar_t__ USB_DR_MODE_PERIPHERAL ; 
 int /*<<< orphan*/  dwc2_set_param_otg_cap (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_set_param_phy_type (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_set_param_phy_utmi_width (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_set_param_power_down (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_set_param_speed (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_set_param_tx_fifo_sizes (struct dwc2_hsotg*) ; 

__attribute__((used)) static void dwc2_set_default_params(struct dwc2_hsotg *hsotg)
{
	struct dwc2_hw_params *hw = &hsotg->hw_params;
	struct dwc2_core_params *p = &hsotg->params;
	bool dma_capable = !(hw->arch == GHWCFG2_SLAVE_ONLY_ARCH);

	dwc2_set_param_otg_cap(hsotg);
	dwc2_set_param_phy_type(hsotg);
	dwc2_set_param_speed(hsotg);
	dwc2_set_param_phy_utmi_width(hsotg);
	dwc2_set_param_power_down(hsotg);
	p->phy_ulpi_ddr = false;
	p->phy_ulpi_ext_vbus = false;

	p->enable_dynamic_fifo = hw->enable_dynamic_fifo;
	p->en_multiple_tx_fifo = hw->en_multiple_tx_fifo;
	p->i2c_enable = hw->i2c_enable;
	p->acg_enable = hw->acg_enable;
	p->ulpi_fs_ls = false;
	p->ts_dline = false;
	p->reload_ctl = (hw->snpsid >= DWC2_CORE_REV_2_92a);
	p->uframe_sched = true;
	p->external_id_pin_ctl = false;
	p->lpm = true;
	p->lpm_clock_gating = true;
	p->besl = true;
	p->hird_threshold_en = true;
	p->hird_threshold = 4;
	p->ipg_isoc_en = false;
	p->max_packet_count = hw->max_packet_count;
	p->max_transfer_size = hw->max_transfer_size;
	p->ahbcfg = GAHBCFG_HBSTLEN_INCR << GAHBCFG_HBSTLEN_SHIFT;

	if ((hsotg->dr_mode == USB_DR_MODE_HOST) ||
	    (hsotg->dr_mode == USB_DR_MODE_OTG)) {
		p->host_dma = dma_capable;
		p->dma_desc_enable = false;
		p->dma_desc_fs_enable = false;
		p->host_support_fs_ls_low_power = false;
		p->host_ls_low_power_phy_clk = false;
		p->host_channels = hw->host_channels;
		p->host_rx_fifo_size = hw->rx_fifo_size;
		p->host_nperio_tx_fifo_size = hw->host_nperio_tx_fifo_size;
		p->host_perio_tx_fifo_size = hw->host_perio_tx_fifo_size;
	}

	if ((hsotg->dr_mode == USB_DR_MODE_PERIPHERAL) ||
	    (hsotg->dr_mode == USB_DR_MODE_OTG)) {
		p->g_dma = dma_capable;
		p->g_dma_desc = hw->dma_desc_enable;

		/*
		 * The values for g_rx_fifo_size (2048) and
		 * g_np_tx_fifo_size (1024) come from the legacy s3c
		 * gadget driver. These defaults have been hard-coded
		 * for some time so many platforms depend on these
		 * values. Leave them as defaults for now and only
		 * auto-detect if the hardware does not support the
		 * default.
		 */
		p->g_rx_fifo_size = 2048;
		p->g_np_tx_fifo_size = 1024;
		dwc2_set_param_tx_fifo_sizes(hsotg);
	}
}
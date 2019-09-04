#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dwc_otg_core_if_t ;
struct TYPE_2__ {int otg_cap; int dma_enable; int dma_desc_enable; int opt; int dma_burst_size; int host_support_fs_ls_low_power; int enable_dynamic_fifo; int data_fifo_size; int dev_rx_fifo_size; int dev_nperio_tx_fifo_size; int host_rx_fifo_size; int host_nperio_tx_fifo_size; int host_perio_tx_fifo_size; int max_transfer_size; int max_packet_count; int host_channels; int dev_endpoints; int phy_type; int speed; int host_ls_low_power_phy_clk; int phy_ulpi_ddr; int phy_ulpi_ext_vbus; int phy_utmi_width; int ulpi_fs_ls; int ts_dline; int i2c_enable; int en_multiple_tx_fifo; int* dev_perio_tx_fifo_size; int* dev_tx_fifo_size; int thr_ctl; int mpi_enable; int pti_enable; int lpm_enable; int ic_usb_cap; int tx_thr_length; int rx_thr_length; int ahb_thr_ratio; int power_down; int reload_ctl; int dev_out_nak; int cont_on_bna; int ahb_single; int otg_ver; int adp_enable; } ;

/* Variables and functions */
 TYPE_1__ dwc_otg_module_params ; 
 scalar_t__ dwc_otg_set_param_adp_enable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_ahb_single (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_ahb_thr_ratio (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_cont_on_bna (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_data_fifo_size (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_dev_endpoints (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_dev_nperio_tx_fifo_size (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_dev_out_nak (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_dev_perio_tx_fifo_size (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ dwc_otg_set_param_dev_rx_fifo_size (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_dev_tx_fifo_size (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ dwc_otg_set_param_dma_burst_size (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_dma_desc_enable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_dma_enable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_en_multiple_tx_fifo (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_enable_dynamic_fifo (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_host_channels (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_host_ls_low_power_phy_clk (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_host_nperio_tx_fifo_size (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_host_perio_tx_fifo_size (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_host_rx_fifo_size (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_host_support_fs_ls_low_power (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_i2c_enable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_ic_usb_cap (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_lpm_enable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_max_packet_count (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_max_transfer_size (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_mpi_enable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_opt (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_otg_cap (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_otg_ver (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_phy_type (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_phy_ulpi_ddr (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_phy_ulpi_ext_vbus (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_phy_utmi_width (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_power_down (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_pti_enable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_reload_ctl (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_rx_thr_length (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_speed (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_thr_ctl (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_ts_dline (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_tx_thr_length (int /*<<< orphan*/ *,int) ; 
 scalar_t__ dwc_otg_set_param_ulpi_fs_ls (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int set_parameters(dwc_otg_core_if_t * core_if)
{
	int retval = 0;
	int i;

	if (dwc_otg_module_params.otg_cap != -1) {
		retval +=
		    dwc_otg_set_param_otg_cap(core_if,
					      dwc_otg_module_params.otg_cap);
	}
	if (dwc_otg_module_params.dma_enable != -1) {
		retval +=
		    dwc_otg_set_param_dma_enable(core_if,
						 dwc_otg_module_params.
						 dma_enable);
	}
	if (dwc_otg_module_params.dma_desc_enable != -1) {
		retval +=
		    dwc_otg_set_param_dma_desc_enable(core_if,
						      dwc_otg_module_params.
						      dma_desc_enable);
	}
	if (dwc_otg_module_params.opt != -1) {
		retval +=
		    dwc_otg_set_param_opt(core_if, dwc_otg_module_params.opt);
	}
	if (dwc_otg_module_params.dma_burst_size != -1) {
		retval +=
		    dwc_otg_set_param_dma_burst_size(core_if,
						     dwc_otg_module_params.
						     dma_burst_size);
	}
	if (dwc_otg_module_params.host_support_fs_ls_low_power != -1) {
		retval +=
		    dwc_otg_set_param_host_support_fs_ls_low_power(core_if,
								   dwc_otg_module_params.
								   host_support_fs_ls_low_power);
	}
	if (dwc_otg_module_params.enable_dynamic_fifo != -1) {
		retval +=
		    dwc_otg_set_param_enable_dynamic_fifo(core_if,
							  dwc_otg_module_params.
							  enable_dynamic_fifo);
	}
	if (dwc_otg_module_params.data_fifo_size != -1) {
		retval +=
		    dwc_otg_set_param_data_fifo_size(core_if,
						     dwc_otg_module_params.
						     data_fifo_size);
	}
	if (dwc_otg_module_params.dev_rx_fifo_size != -1) {
		retval +=
		    dwc_otg_set_param_dev_rx_fifo_size(core_if,
						       dwc_otg_module_params.
						       dev_rx_fifo_size);
	}
	if (dwc_otg_module_params.dev_nperio_tx_fifo_size != -1) {
		retval +=
		    dwc_otg_set_param_dev_nperio_tx_fifo_size(core_if,
							      dwc_otg_module_params.
							      dev_nperio_tx_fifo_size);
	}
	if (dwc_otg_module_params.host_rx_fifo_size != -1) {
		retval +=
		    dwc_otg_set_param_host_rx_fifo_size(core_if,
							dwc_otg_module_params.host_rx_fifo_size);
	}
	if (dwc_otg_module_params.host_nperio_tx_fifo_size != -1) {
		retval +=
		    dwc_otg_set_param_host_nperio_tx_fifo_size(core_if,
							       dwc_otg_module_params.
							       host_nperio_tx_fifo_size);
	}
	if (dwc_otg_module_params.host_perio_tx_fifo_size != -1) {
		retval +=
		    dwc_otg_set_param_host_perio_tx_fifo_size(core_if,
							      dwc_otg_module_params.
							      host_perio_tx_fifo_size);
	}
	if (dwc_otg_module_params.max_transfer_size != -1) {
		retval +=
		    dwc_otg_set_param_max_transfer_size(core_if,
							dwc_otg_module_params.
							max_transfer_size);
	}
	if (dwc_otg_module_params.max_packet_count != -1) {
		retval +=
		    dwc_otg_set_param_max_packet_count(core_if,
						       dwc_otg_module_params.
						       max_packet_count);
	}
	if (dwc_otg_module_params.host_channels != -1) {
		retval +=
		    dwc_otg_set_param_host_channels(core_if,
						    dwc_otg_module_params.
						    host_channels);
	}
	if (dwc_otg_module_params.dev_endpoints != -1) {
		retval +=
		    dwc_otg_set_param_dev_endpoints(core_if,
						    dwc_otg_module_params.
						    dev_endpoints);
	}
	if (dwc_otg_module_params.phy_type != -1) {
		retval +=
		    dwc_otg_set_param_phy_type(core_if,
					       dwc_otg_module_params.phy_type);
	}
	if (dwc_otg_module_params.speed != -1) {
		retval +=
		    dwc_otg_set_param_speed(core_if,
					    dwc_otg_module_params.speed);
	}
	if (dwc_otg_module_params.host_ls_low_power_phy_clk != -1) {
		retval +=
		    dwc_otg_set_param_host_ls_low_power_phy_clk(core_if,
								dwc_otg_module_params.
								host_ls_low_power_phy_clk);
	}
	if (dwc_otg_module_params.phy_ulpi_ddr != -1) {
		retval +=
		    dwc_otg_set_param_phy_ulpi_ddr(core_if,
						   dwc_otg_module_params.
						   phy_ulpi_ddr);
	}
	if (dwc_otg_module_params.phy_ulpi_ext_vbus != -1) {
		retval +=
		    dwc_otg_set_param_phy_ulpi_ext_vbus(core_if,
							dwc_otg_module_params.
							phy_ulpi_ext_vbus);
	}
	if (dwc_otg_module_params.phy_utmi_width != -1) {
		retval +=
		    dwc_otg_set_param_phy_utmi_width(core_if,
						     dwc_otg_module_params.
						     phy_utmi_width);
	}
	if (dwc_otg_module_params.ulpi_fs_ls != -1) {
		retval +=
		    dwc_otg_set_param_ulpi_fs_ls(core_if,
						 dwc_otg_module_params.ulpi_fs_ls);
	}
	if (dwc_otg_module_params.ts_dline != -1) {
		retval +=
		    dwc_otg_set_param_ts_dline(core_if,
					       dwc_otg_module_params.ts_dline);
	}
	if (dwc_otg_module_params.i2c_enable != -1) {
		retval +=
		    dwc_otg_set_param_i2c_enable(core_if,
						 dwc_otg_module_params.
						 i2c_enable);
	}
	if (dwc_otg_module_params.en_multiple_tx_fifo != -1) {
		retval +=
		    dwc_otg_set_param_en_multiple_tx_fifo(core_if,
							  dwc_otg_module_params.
							  en_multiple_tx_fifo);
	}
	for (i = 0; i < 15; i++) {
		if (dwc_otg_module_params.dev_perio_tx_fifo_size[i] != -1) {
			retval +=
			    dwc_otg_set_param_dev_perio_tx_fifo_size(core_if,
								     dwc_otg_module_params.
								     dev_perio_tx_fifo_size
								     [i], i);
		}
	}

	for (i = 0; i < 15; i++) {
		if (dwc_otg_module_params.dev_tx_fifo_size[i] != -1) {
			retval += dwc_otg_set_param_dev_tx_fifo_size(core_if,
								     dwc_otg_module_params.
								     dev_tx_fifo_size
								     [i], i);
		}
	}
	if (dwc_otg_module_params.thr_ctl != -1) {
		retval +=
		    dwc_otg_set_param_thr_ctl(core_if,
					      dwc_otg_module_params.thr_ctl);
	}
	if (dwc_otg_module_params.mpi_enable != -1) {
		retval +=
		    dwc_otg_set_param_mpi_enable(core_if,
						 dwc_otg_module_params.
						 mpi_enable);
	}
	if (dwc_otg_module_params.pti_enable != -1) {
		retval +=
		    dwc_otg_set_param_pti_enable(core_if,
						 dwc_otg_module_params.
						 pti_enable);
	}
	if (dwc_otg_module_params.lpm_enable != -1) {
		retval +=
		    dwc_otg_set_param_lpm_enable(core_if,
						 dwc_otg_module_params.
						 lpm_enable);
	}
	if (dwc_otg_module_params.ic_usb_cap != -1) {
		retval +=
		    dwc_otg_set_param_ic_usb_cap(core_if,
						 dwc_otg_module_params.
						 ic_usb_cap);
	}
	if (dwc_otg_module_params.tx_thr_length != -1) {
		retval +=
		    dwc_otg_set_param_tx_thr_length(core_if,
						    dwc_otg_module_params.tx_thr_length);
	}
	if (dwc_otg_module_params.rx_thr_length != -1) {
		retval +=
		    dwc_otg_set_param_rx_thr_length(core_if,
						    dwc_otg_module_params.
						    rx_thr_length);
	}
	if (dwc_otg_module_params.ahb_thr_ratio != -1) {
		retval +=
		    dwc_otg_set_param_ahb_thr_ratio(core_if,
						    dwc_otg_module_params.ahb_thr_ratio);
	}
	if (dwc_otg_module_params.power_down != -1) {
		retval +=
		    dwc_otg_set_param_power_down(core_if,
						 dwc_otg_module_params.power_down);
	}
	if (dwc_otg_module_params.reload_ctl != -1) {
		retval +=
		    dwc_otg_set_param_reload_ctl(core_if,
						 dwc_otg_module_params.reload_ctl);
	}

	if (dwc_otg_module_params.dev_out_nak != -1) {
		retval +=
			dwc_otg_set_param_dev_out_nak(core_if,
			dwc_otg_module_params.dev_out_nak);
	}

	if (dwc_otg_module_params.cont_on_bna != -1) {
		retval +=
			dwc_otg_set_param_cont_on_bna(core_if,
			dwc_otg_module_params.cont_on_bna);
	}

	if (dwc_otg_module_params.ahb_single != -1) {
		retval +=
			dwc_otg_set_param_ahb_single(core_if,
			dwc_otg_module_params.ahb_single);
	}

	if (dwc_otg_module_params.otg_ver != -1) {
		retval +=
		    dwc_otg_set_param_otg_ver(core_if,
					      dwc_otg_module_params.otg_ver);
	}
	if (dwc_otg_module_params.adp_enable != -1) {
		retval +=
		    dwc_otg_set_param_adp_enable(core_if,
						 dwc_otg_module_params.
						 adp_enable);
	}
	return retval;
}
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
struct dwc2_core_params {int host_rx_fifo_size; int host_nperio_tx_fifo_size; int host_perio_tx_fifo_size; int max_packet_count; int i2c_enable; int activate_stm_fs_transceiver; int /*<<< orphan*/  phy_type; int /*<<< orphan*/  speed; int /*<<< orphan*/  otg_cap; } ;
struct dwc2_hsotg {struct dwc2_core_params params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE ; 
 int /*<<< orphan*/  DWC2_PHY_TYPE_PARAM_FS ; 
 int /*<<< orphan*/  DWC2_SPEED_PARAM_FULL ; 

__attribute__((used)) static void dwc2_set_stm32f4x9_fsotg_params(struct dwc2_hsotg *hsotg)
{
	struct dwc2_core_params *p = &hsotg->params;

	p->otg_cap = DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE;
	p->speed = DWC2_SPEED_PARAM_FULL;
	p->host_rx_fifo_size = 128;
	p->host_nperio_tx_fifo_size = 96;
	p->host_perio_tx_fifo_size = 96;
	p->max_packet_count = 256;
	p->phy_type = DWC2_PHY_TYPE_PARAM_FS;
	p->i2c_enable = false;
	p->activate_stm_fs_transceiver = true;
}
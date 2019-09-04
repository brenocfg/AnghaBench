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
struct dwc2_core_params {int host_rx_fifo_size; int host_nperio_tx_fifo_size; int host_perio_tx_fifo_size; int host_channels; int ahbcfg; int /*<<< orphan*/  power_down; int /*<<< orphan*/  phy_type; int /*<<< orphan*/  speed; int /*<<< orphan*/  otg_cap; } ;
struct dwc2_hsotg {struct dwc2_core_params params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE ; 
 int /*<<< orphan*/  DWC2_PHY_TYPE_PARAM_UTMI ; 
 int /*<<< orphan*/  DWC2_POWER_DOWN_PARAM_NONE ; 
 int /*<<< orphan*/  DWC2_SPEED_PARAM_HIGH ; 
 int GAHBCFG_HBSTLEN_INCR8 ; 
 int GAHBCFG_HBSTLEN_SHIFT ; 

__attribute__((used)) static void dwc2_set_amlogic_params(struct dwc2_hsotg *hsotg)
{
	struct dwc2_core_params *p = &hsotg->params;

	p->otg_cap = DWC2_CAP_PARAM_NO_HNP_SRP_CAPABLE;
	p->speed = DWC2_SPEED_PARAM_HIGH;
	p->host_rx_fifo_size = 512;
	p->host_nperio_tx_fifo_size = 500;
	p->host_perio_tx_fifo_size = 500;
	p->host_channels = 16;
	p->phy_type = DWC2_PHY_TYPE_PARAM_UTMI;
	p->ahbcfg = GAHBCFG_HBSTLEN_INCR8 <<
		GAHBCFG_HBSTLEN_SHIFT;
	p->power_down = DWC2_POWER_DOWN_PARAM_NONE;
}
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
struct dwc2_core_params {int host_rx_fifo_size; int max_transfer_size; int max_packet_count; int ahbcfg; } ;
struct dwc2_hsotg {struct dwc2_core_params params; } ;

/* Variables and functions */

__attribute__((used)) static void dwc2_set_bcm_params(struct dwc2_hsotg *hsotg)
{
	struct dwc2_core_params *p = &hsotg->params;

	p->host_rx_fifo_size = 774;
	p->max_transfer_size = 65535;
	p->max_packet_count = 511;
	p->ahbcfg = 0x10;
}
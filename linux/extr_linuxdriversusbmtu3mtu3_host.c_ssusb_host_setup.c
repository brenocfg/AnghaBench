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
struct otg_switch_mtk {scalar_t__ manual_drd_enabled; } ;
struct ssusb_mtk {struct otg_switch_mtk otg_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTU3_DR_FORCE_HOST ; 
 int /*<<< orphan*/  host_ports_num_get (struct ssusb_mtk*) ; 
 int /*<<< orphan*/  ssusb_host_enable (struct ssusb_mtk*) ; 
 int /*<<< orphan*/  ssusb_set_force_mode (struct ssusb_mtk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssusb_set_vbus (struct otg_switch_mtk*,int) ; 

__attribute__((used)) static void ssusb_host_setup(struct ssusb_mtk *ssusb)
{
	struct otg_switch_mtk *otg_sx = &ssusb->otg_switch;

	host_ports_num_get(ssusb);

	/*
	 * power on host and power on/enable all ports
	 * if support OTG, gadget driver will switch port0 to device mode
	 */
	ssusb_host_enable(ssusb);

	if (otg_sx->manual_drd_enabled)
		ssusb_set_force_mode(ssusb, MTU3_DR_FORCE_HOST);

	/* if port0 supports dual-role, works as host mode by default */
	ssusb_set_vbus(&ssusb->otg_switch, 1);
}
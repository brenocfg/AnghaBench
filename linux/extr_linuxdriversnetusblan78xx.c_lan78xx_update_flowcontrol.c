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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct lan78xx_net {int fc_request_control; int /*<<< orphan*/  net; TYPE_1__* udev; scalar_t__ fc_autoneg; } ;
struct TYPE_2__ {scalar_t__ speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCT_FLOW ; 
 int /*<<< orphan*/  FLOW ; 
 int FLOW_CR_RX_FCEN_ ; 
 int FLOW_CR_TX_FCEN_ ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 
 scalar_t__ USB_SPEED_HIGH ; 
 scalar_t__ USB_SPEED_SUPER ; 
 int lan78xx_write_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  link ; 
 int mii_resolve_flowctrl_fdx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct lan78xx_net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static int lan78xx_update_flowcontrol(struct lan78xx_net *dev, u8 duplex,
				      u16 lcladv, u16 rmtadv)
{
	u32 flow = 0, fct_flow = 0;
	int ret;
	u8 cap;

	if (dev->fc_autoneg)
		cap = mii_resolve_flowctrl_fdx(lcladv, rmtadv);
	else
		cap = dev->fc_request_control;

	if (cap & FLOW_CTRL_TX)
		flow |= (FLOW_CR_TX_FCEN_ | 0xFFFF);

	if (cap & FLOW_CTRL_RX)
		flow |= FLOW_CR_RX_FCEN_;

	if (dev->udev->speed == USB_SPEED_SUPER)
		fct_flow = 0x817;
	else if (dev->udev->speed == USB_SPEED_HIGH)
		fct_flow = 0x211;

	netif_dbg(dev, link, dev->net, "rx pause %s, tx pause %s",
		  (cap & FLOW_CTRL_RX ? "enabled" : "disabled"),
		  (cap & FLOW_CTRL_TX ? "enabled" : "disabled"));

	ret = lan78xx_write_reg(dev, FCT_FLOW, fct_flow);

	/* threshold value should be set before enabling flow */
	ret = lan78xx_write_reg(dev, FLOW, flow);

	return 0;
}
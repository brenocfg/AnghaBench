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
struct ast_vhub_port {int /*<<< orphan*/  dev; scalar_t__ change; int /*<<< orphan*/  status; } ;
struct ast_vhub {scalar_t__ speed; int suspended; int wakeup_en; scalar_t__ regs; struct ast_vhub_port* ports; } ;

/* Variables and functions */
 scalar_t__ AST_VHUB_CONF ; 
 scalar_t__ AST_VHUB_EP0_CTRL ; 
 scalar_t__ AST_VHUB_EP1_CTRL ; 
 scalar_t__ AST_VHUB_EP1_STS_CHG ; 
 unsigned int AST_VHUB_NUM_PORTS ; 
 int /*<<< orphan*/  UDCDBG (struct ast_vhub*,char*) ; 
 int /*<<< orphan*/  USB_PORT_STAT_CONNECTION ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int VHUB_EP1_CTRL_ENABLE ; 
 int VHUB_EP1_CTRL_RESET_TOGGLE ; 
 int /*<<< orphan*/  ast_vhub_dev_suspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void ast_vhub_hub_reset(struct ast_vhub *vhub)
{
	unsigned int i;

	UDCDBG(vhub, "USB bus reset\n");

	/*
	 * Is the speed known ? If not we don't care, we aren't
	 * initialized yet and ports haven't been enabled.
	 */
	if (vhub->speed == USB_SPEED_UNKNOWN)
		return;

	/* We aren't suspended anymore obviously */
	vhub->suspended = false;

	/* No speed set */
	vhub->speed = USB_SPEED_UNKNOWN;

	/* Wakeup not enabled anymore */
	vhub->wakeup_en = false;

	/*
	 * Clear all port status, disable gadgets and "suspend"
	 * them. They will be woken up by a port reset.
	 */
	for (i = 0; i < AST_VHUB_NUM_PORTS; i++) {
		struct ast_vhub_port *p = &vhub->ports[i];

		/* Only keep the connected flag */
		p->status &= USB_PORT_STAT_CONNECTION;
		p->change = 0;

		/* Suspend the gadget if any */
		ast_vhub_dev_suspend(&p->dev);
	}

	/* Cleanup HW */
	writel(0, vhub->regs + AST_VHUB_CONF);
	writel(0, vhub->regs + AST_VHUB_EP0_CTRL);
	writel(VHUB_EP1_CTRL_RESET_TOGGLE |
	       VHUB_EP1_CTRL_ENABLE,
	       vhub->regs + AST_VHUB_EP1_CTRL);
	writel(0, vhub->regs + AST_VHUB_EP1_STS_CHG);
}
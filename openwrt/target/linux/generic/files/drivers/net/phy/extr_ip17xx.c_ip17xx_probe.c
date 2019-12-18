#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct switch_dev {int /*<<< orphan*/  name; int /*<<< orphan*/ * ops; int /*<<< orphan*/  ports; int /*<<< orphan*/  cpu_port; int /*<<< orphan*/  vlans; } ;
struct TYPE_4__ {scalar_t__ addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;
struct phy_device {TYPE_2__ mdio; struct ip17xx_state* priv; } ;
struct ip17xx_state {TYPE_1__* regs; int /*<<< orphan*/  mii_bus; struct switch_dev dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  NAME; int /*<<< orphan*/  NUM_PORTS; int /*<<< orphan*/  CPU_PORT; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_VLANS ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int get_model (struct ip17xx_state*) ; 
 int /*<<< orphan*/  ip17xx_ops ; 
 int /*<<< orphan*/  kfree (struct ip17xx_state*) ; 
 struct ip17xx_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip17xx_probe(struct phy_device *pdev)
{
	struct ip17xx_state *state;
	struct switch_dev *dev;
	int err;

	/* We only attach to PHY 0, but use all available PHYs */
	if (pdev->mdio.addr != 0)
		return -ENODEV;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return -ENOMEM;

	dev = &state->dev;

	pdev->priv = state;
	state->mii_bus = pdev->mdio.bus;

	err = get_model(state);
	if (err < 0)
		goto error;

	dev->vlans = MAX_VLANS;
	dev->cpu_port = state->regs->CPU_PORT;
	dev->ports = state->regs->NUM_PORTS;
	dev->name = state->regs->NAME;
	dev->ops = &ip17xx_ops;

	pr_info("IP17xx: Found %s at %s\n", dev->name, dev_name(&pdev->mdio.dev));
	return 0;

error:
	kfree(state);
	return err;
}
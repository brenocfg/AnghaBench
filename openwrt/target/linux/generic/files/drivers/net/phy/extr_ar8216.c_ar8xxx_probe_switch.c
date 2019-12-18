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
struct switch_dev {int /*<<< orphan*/  ops; int /*<<< orphan*/  ports; int /*<<< orphan*/  vlans; int /*<<< orphan*/  name; int /*<<< orphan*/  cpu_port; } ;
struct ar8xxx_priv {struct switch_dev dev; struct ar8xxx_chip* chip; } ;
struct ar8xxx_chip {int /*<<< orphan*/  swops; int /*<<< orphan*/  ports; int /*<<< orphan*/  vlans; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8216_PORT_CPU ; 
 int ar8xxx_mib_init (struct ar8xxx_priv*) ; 

__attribute__((used)) static int
ar8xxx_probe_switch(struct ar8xxx_priv *priv)
{
	const struct ar8xxx_chip *chip;
	struct switch_dev *swdev;
	int ret;

	chip = priv->chip;

	swdev = &priv->dev;
	swdev->cpu_port = AR8216_PORT_CPU;
	swdev->name = chip->name;
	swdev->vlans = chip->vlans;
	swdev->ports = chip->ports;
	swdev->ops = chip->swops;

	ret = ar8xxx_mib_init(priv);
	if (ret)
		return ret;

	return 0;
}
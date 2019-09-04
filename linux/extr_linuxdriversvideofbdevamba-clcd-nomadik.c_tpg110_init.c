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
struct device_node {int /*<<< orphan*/  fwnode; } ;
struct device {int dummy; } ;
struct clcd_board {int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  devm_fwnode_get_gpiod_from_child (struct device*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grestb ; 
 int /*<<< orphan*/  scen ; 
 int /*<<< orphan*/  scl ; 
 int /*<<< orphan*/  sda ; 
 int /*<<< orphan*/  tpg110_disable ; 
 int /*<<< orphan*/  tpg110_enable ; 

__attribute__((used)) static void tpg110_init(struct device *dev, struct device_node *np,
			struct clcd_board *board)
{
	dev_info(dev, "TPG110 display init\n");

	/* This asserts the GRESTB signal, putting the display into reset */
	grestb = devm_fwnode_get_gpiod_from_child(dev, "grestb", &np->fwnode,
						  GPIOD_OUT_HIGH, "grestb");
	if (IS_ERR(grestb)) {
		dev_err(dev, "no GRESTB GPIO\n");
		return;
	}
	scen = devm_fwnode_get_gpiod_from_child(dev, "scen", &np->fwnode,
						GPIOD_OUT_LOW, "scen");
	if (IS_ERR(scen)) {
		dev_err(dev, "no SCEN GPIO\n");
		return;
	}
	scl = devm_fwnode_get_gpiod_from_child(dev, "scl", &np->fwnode,
					       GPIOD_OUT_LOW, "scl");
	if (IS_ERR(scl)) {
		dev_err(dev, "no SCL GPIO\n");
		return;
	}
	sda = devm_fwnode_get_gpiod_from_child(dev, "sda", &np->fwnode,
					       GPIOD_OUT_LOW, "sda");
	if (IS_ERR(sda)) {
		dev_err(dev, "no SDA GPIO\n");
		return;
	}
	board->enable = tpg110_enable;
	board->disable = tpg110_disable;
}
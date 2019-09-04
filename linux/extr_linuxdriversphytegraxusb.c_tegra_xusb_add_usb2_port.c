#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lane; TYPE_4__* ops; } ;
struct tegra_xusb_usb2_port {TYPE_5__ base; } ;
struct tegra_xusb_padctl {int /*<<< orphan*/  ports; TYPE_3__* soc; int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* map ) (TYPE_5__*) ;} ;
struct TYPE_8__ {TYPE_4__* ops; } ;
struct TYPE_9__ {TYPE_1__ usb2; } ;
struct TYPE_10__ {TYPE_2__ ports; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct tegra_xusb_usb2_port* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 struct device_node* tegra_xusb_find_port_node (struct tegra_xusb_padctl*,char*,unsigned int) ; 
 int tegra_xusb_port_init (TYPE_5__*,struct tegra_xusb_padctl*,struct device_node*,char*,unsigned int) ; 
 int /*<<< orphan*/  tegra_xusb_port_unregister (TYPE_5__*) ; 
 int tegra_xusb_usb2_port_parse_dt (struct tegra_xusb_usb2_port*) ; 

__attribute__((used)) static int tegra_xusb_add_usb2_port(struct tegra_xusb_padctl *padctl,
				    unsigned int index)
{
	struct tegra_xusb_usb2_port *usb2;
	struct device_node *np;
	int err = 0;

	/*
	 * USB2 ports don't require additional properties, but if the port is
	 * marked as disabled there is no reason to register it.
	 */
	np = tegra_xusb_find_port_node(padctl, "usb2", index);
	if (!np || !of_device_is_available(np))
		goto out;

	usb2 = devm_kzalloc(padctl->dev, sizeof(*usb2), GFP_KERNEL);
	if (!usb2) {
		err = -ENOMEM;
		goto out;
	}

	err = tegra_xusb_port_init(&usb2->base, padctl, np, "usb2", index);
	if (err < 0)
		goto out;

	usb2->base.ops = padctl->soc->ports.usb2.ops;

	usb2->base.lane = usb2->base.ops->map(&usb2->base);
	if (IS_ERR(usb2->base.lane)) {
		err = PTR_ERR(usb2->base.lane);
		goto out;
	}

	err = tegra_xusb_usb2_port_parse_dt(usb2);
	if (err < 0) {
		tegra_xusb_port_unregister(&usb2->base);
		goto out;
	}

	list_add_tail(&usb2->base.list, &padctl->ports);

out:
	of_node_put(np);
	return err;
}
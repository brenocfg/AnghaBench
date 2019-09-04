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
struct tegra_xusb_ulpi_port {TYPE_5__ base; } ;
struct tegra_xusb_padctl {int /*<<< orphan*/  ports; TYPE_3__* soc; int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* map ) (TYPE_5__*) ;} ;
struct TYPE_8__ {TYPE_4__* ops; } ;
struct TYPE_9__ {TYPE_1__ ulpi; } ;
struct TYPE_10__ {TYPE_2__ ports; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct tegra_xusb_ulpi_port* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 struct device_node* tegra_xusb_find_port_node (struct tegra_xusb_padctl*,char*,unsigned int) ; 
 int tegra_xusb_port_init (TYPE_5__*,struct tegra_xusb_padctl*,struct device_node*,char*,unsigned int) ; 
 int /*<<< orphan*/  tegra_xusb_port_unregister (TYPE_5__*) ; 
 int tegra_xusb_ulpi_port_parse_dt (struct tegra_xusb_ulpi_port*) ; 

__attribute__((used)) static int tegra_xusb_add_ulpi_port(struct tegra_xusb_padctl *padctl,
				    unsigned int index)
{
	struct tegra_xusb_ulpi_port *ulpi;
	struct device_node *np;
	int err = 0;

	np = tegra_xusb_find_port_node(padctl, "ulpi", index);
	if (!np || !of_device_is_available(np))
		goto out;

	ulpi = devm_kzalloc(padctl->dev, sizeof(*ulpi), GFP_KERNEL);
	if (!ulpi) {
		err = -ENOMEM;
		goto out;
	}

	err = tegra_xusb_port_init(&ulpi->base, padctl, np, "ulpi", index);
	if (err < 0)
		goto out;

	ulpi->base.ops = padctl->soc->ports.ulpi.ops;

	ulpi->base.lane = ulpi->base.ops->map(&ulpi->base);
	if (IS_ERR(ulpi->base.lane)) {
		err = PTR_ERR(ulpi->base.lane);
		goto out;
	}

	err = tegra_xusb_ulpi_port_parse_dt(ulpi);
	if (err < 0) {
		tegra_xusb_port_unregister(&ulpi->base);
		goto out;
	}

	list_add_tail(&ulpi->base.list, &padctl->ports);

out:
	of_node_put(np);
	return err;
}
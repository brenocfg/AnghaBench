#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tegra_xusb_padctl {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {struct device_node* of_node; int /*<<< orphan*/ * type; int /*<<< orphan*/  parent; } ;
struct tegra_xusb_pad {TYPE_2__ dev; TYPE_1__* soc; struct tegra_xusb_padctl* padctl; int /*<<< orphan*/  list; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  tegra_xusb_pad_type ; 

int tegra_xusb_pad_init(struct tegra_xusb_pad *pad,
			struct tegra_xusb_padctl *padctl,
			struct device_node *np)
{
	int err;

	device_initialize(&pad->dev);
	INIT_LIST_HEAD(&pad->list);
	pad->dev.parent = padctl->dev;
	pad->dev.type = &tegra_xusb_pad_type;
	pad->dev.of_node = np;
	pad->padctl = padctl;

	err = dev_set_name(&pad->dev, "%s", pad->soc->name);
	if (err < 0)
		goto unregister;

	err = device_add(&pad->dev);
	if (err < 0)
		goto unregister;

	return 0;

unregister:
	device_unregister(&pad->dev);
	return err;
}
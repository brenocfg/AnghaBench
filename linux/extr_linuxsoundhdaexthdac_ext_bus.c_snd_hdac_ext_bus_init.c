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
struct hdac_io_ops {int dummy; } ;
struct hdac_ext_bus_ops {int dummy; } ;
struct hdac_bus_ops {int dummy; } ;
struct hdac_bus {int cmd_dma_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  idx; int /*<<< orphan*/  hlink_list; struct hdac_ext_bus_ops const* ext_ops; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct hdac_io_ops hdac_ext_default_io ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_hdac_bus_init (struct hdac_bus*,struct device*,struct hdac_bus_ops const*,struct hdac_io_ops const*) ; 

int snd_hdac_ext_bus_init(struct hdac_bus *bus, struct device *dev,
			const struct hdac_bus_ops *ops,
			const struct hdac_io_ops *io_ops,
			const struct hdac_ext_bus_ops *ext_ops)
{
	int ret;
	static int idx;

	/* check if io ops are provided, if not load the defaults */
	if (io_ops == NULL)
		io_ops = &hdac_ext_default_io;

	ret = snd_hdac_bus_init(bus, dev, ops, io_ops);
	if (ret < 0)
		return ret;

	bus->ext_ops = ext_ops;
	INIT_LIST_HEAD(&bus->hlink_list);
	bus->idx = idx++;

	mutex_init(&bus->lock);
	bus->cmd_dma_state = true;

	return 0;
}
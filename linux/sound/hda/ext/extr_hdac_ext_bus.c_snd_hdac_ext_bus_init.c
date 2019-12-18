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
struct hdac_ext_bus_ops {int dummy; } ;
struct hdac_bus_ops {int dummy; } ;
struct hdac_bus {int cmd_dma_state; scalar_t__ idx; struct hdac_ext_bus_ops const* ext_ops; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int snd_hdac_bus_init (struct hdac_bus*,struct device*,struct hdac_bus_ops const*) ; 

int snd_hdac_ext_bus_init(struct hdac_bus *bus, struct device *dev,
			const struct hdac_bus_ops *ops,
			const struct hdac_ext_bus_ops *ext_ops)
{
	int ret;

	ret = snd_hdac_bus_init(bus, dev, ops);
	if (ret < 0)
		return ret;

	bus->ext_ops = ext_ops;
	/* FIXME:
	 * Currently only one bus is supported, if there is device with more
	 * buses, bus->idx should be greater than 0, but there needs to be a
	 * reliable way to always assign same number.
	 */
	bus->idx = 0;
	bus->cmd_dma_state = true;

	return 0;
}
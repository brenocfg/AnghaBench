#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fifosize; scalar_t__ type; } ;
struct sci_port {TYPE_1__ port; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; struct plat_sci_port* platform_data; scalar_t__ of_node; } ;
struct platform_device {unsigned int id; TYPE_2__ dev; } ;
struct plat_sci_port {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  attr; } ;
struct TYPE_7__ {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int EINVAL ; 
 scalar_t__ PORT_HSCIF ; 
 scalar_t__ PORT_SCIFA ; 
 scalar_t__ PORT_SCIFB ; 
 TYPE_4__ dev_attr_rx_fifo_timeout ; 
 TYPE_3__ dev_attr_rx_fifo_trigger ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 scalar_t__ is_early_platform_device (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sci_port*) ; 
 struct plat_sci_port* sci_parse_dt (struct platform_device*,unsigned int*) ; 
 struct sci_port* sci_ports ; 
 int /*<<< orphan*/  sci_ports_in_use ; 
 int sci_probe_earlyprintk (struct platform_device*) ; 
 int sci_probe_single (struct platform_device*,unsigned int,struct plat_sci_port*,struct sci_port*) ; 
 int sysfs_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sci_probe(struct platform_device *dev)
{
	struct plat_sci_port *p;
	struct sci_port *sp;
	unsigned int dev_id;
	int ret;

	/*
	 * If we've come here via earlyprintk initialization, head off to
	 * the special early probe. We don't have sufficient device state
	 * to make it beyond this yet.
	 */
	if (is_early_platform_device(dev))
		return sci_probe_earlyprintk(dev);

	if (dev->dev.of_node) {
		p = sci_parse_dt(dev, &dev_id);
		if (p == NULL)
			return -EINVAL;
	} else {
		p = dev->dev.platform_data;
		if (p == NULL) {
			dev_err(&dev->dev, "no platform data supplied\n");
			return -EINVAL;
		}

		dev_id = dev->id;
	}

	sp = &sci_ports[dev_id];
	platform_set_drvdata(dev, sp);

	ret = sci_probe_single(dev, dev_id, p, sp);
	if (ret)
		return ret;

	if (sp->port.fifosize > 1) {
		ret = sysfs_create_file(&dev->dev.kobj,
				&dev_attr_rx_fifo_trigger.attr);
		if (ret)
			return ret;
	}
	if (sp->port.type == PORT_SCIFA || sp->port.type == PORT_SCIFB ||
	    sp->port.type == PORT_HSCIF) {
		ret = sysfs_create_file(&dev->dev.kobj,
				&dev_attr_rx_fifo_timeout.attr);
		if (ret) {
			if (sp->port.fifosize > 1) {
				sysfs_remove_file(&dev->dev.kobj,
					&dev_attr_rx_fifo_trigger.attr);
			}
			return ret;
		}
	}

#ifdef CONFIG_SH_STANDARD_BIOS
	sh_bios_gdb_detach();
#endif

	sci_ports_in_use |= BIT(dev_id);
	return 0;
}
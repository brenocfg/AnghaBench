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
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  h3600_pcmcia_ops ; 
 scalar_t__ machine_is_h3100 () ; 
 scalar_t__ machine_is_h3600 () ; 
 int sa11xx_drv_pcmcia_probe (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int pcmcia_h3600_init(struct device *dev)
{
	int ret = -ENODEV;

	if (machine_is_h3600() || machine_is_h3100())
		ret = sa11xx_drv_pcmcia_probe(dev, &h3600_pcmcia_ops, 0, 2);

	return ret;
}
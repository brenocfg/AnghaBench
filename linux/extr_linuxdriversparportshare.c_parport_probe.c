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
struct parport_driver {int (* probe ) (struct pardevice*) ;int /*<<< orphan*/  name; } ;
struct pardevice {int /*<<< orphan*/  name; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ is_parport (struct device*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct pardevice*) ; 
 struct pardevice* to_pardevice (struct device*) ; 
 struct parport_driver* to_parport_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parport_probe(struct device *dev)
{
	struct parport_driver *drv;

	if (is_parport(dev))
		return -ENODEV;

	drv = to_parport_driver(dev->driver);
	if (!drv->probe) {
		/* if driver has not defined a custom probe */
		struct pardevice *par_dev = to_pardevice(dev);

		if (strcmp(par_dev->name, drv->name))
			return -ENODEV;
		return 0;
	}
	/* if driver defined its own probe */
	return drv->probe(to_pardevice(dev));
}
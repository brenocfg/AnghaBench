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
struct nubus_driver {int (* remove ) (int /*<<< orphan*/ ) ;} ;
struct device {scalar_t__ driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_nubus_board (struct device*) ; 
 struct nubus_driver* to_nubus_driver (scalar_t__) ; 

__attribute__((used)) static int nubus_device_remove(struct device *dev)
{
	struct nubus_driver *ndrv = to_nubus_driver(dev->driver);
	int err = -ENODEV;

	if (dev->driver && ndrv->remove)
		err = ndrv->remove(to_nubus_board(dev));
	return err;
}
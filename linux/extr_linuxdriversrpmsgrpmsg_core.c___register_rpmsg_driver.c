#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct module* owner; int /*<<< orphan*/ * bus; } ;
struct rpmsg_driver {TYPE_1__ drv; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  rpmsg_bus ; 

int __register_rpmsg_driver(struct rpmsg_driver *rpdrv, struct module *owner)
{
	rpdrv->drv.bus = &rpmsg_bus;
	rpdrv->drv.owner = owner;
	return driver_register(&rpdrv->drv);
}
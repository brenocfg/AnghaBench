#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uio_port {scalar_t__ size; TYPE_3__* portio; } ;
struct uio_mem {scalar_t__ size; TYPE_1__* map; } ;
struct uio_device {int /*<<< orphan*/ * portio_dir; TYPE_2__* info; int /*<<< orphan*/ * map_dir; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {struct uio_port* port; struct uio_mem* mem; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int MAX_UIO_MAPS ; 
 int MAX_UIO_PORT_REGIONS ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uio_dev_del_attributes(struct uio_device *idev)
{
	int i;
	struct uio_mem *mem;
	struct uio_port *port;

	for (i = 0; i < MAX_UIO_MAPS; i++) {
		mem = &idev->info->mem[i];
		if (mem->size == 0)
			break;
		kobject_put(&mem->map->kobj);
	}
	kobject_put(idev->map_dir);

	for (i = 0; i < MAX_UIO_PORT_REGIONS; i++) {
		port = &idev->info->port[i];
		if (port->size == 0)
			break;
		kobject_put(&port->portio->kobj);
	}
	kobject_put(idev->portio_dir);
}
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
struct TYPE_2__ {int /*<<< orphan*/  shutdown; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; int /*<<< orphan*/ * bus; } ;
struct hdac_driver {TYPE_1__ driver; scalar_t__ shutdown; scalar_t__ remove; scalar_t__ probe; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_DEV_ASOC ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  hda_ext_drv_probe ; 
 int /*<<< orphan*/  hdac_ext_drv_remove ; 
 int /*<<< orphan*/  hdac_ext_drv_shutdown ; 
 int /*<<< orphan*/  snd_hda_bus_type ; 

int snd_hda_ext_driver_register(struct hdac_driver *drv)
{
	drv->type = HDA_DEV_ASOC;
	drv->driver.bus = &snd_hda_bus_type;
	/* we use default match */

	if (drv->probe)
		drv->driver.probe = hda_ext_drv_probe;
	if (drv->remove)
		drv->driver.remove = hdac_ext_drv_remove;
	if (drv->shutdown)
		drv->driver.shutdown = hdac_ext_drv_shutdown;

	return driver_register(&drv->driver);
}
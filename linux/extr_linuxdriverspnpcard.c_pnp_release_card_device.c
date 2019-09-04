#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pnp_dev {int /*<<< orphan*/  dev; TYPE_1__* card_link; } ;
struct TYPE_4__ {int /*<<< orphan*/ * remove; } ;
struct pnp_card_driver {TYPE_2__ link; } ;
struct TYPE_3__ {struct pnp_card_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  card_remove ; 
 int /*<<< orphan*/  card_remove_first ; 
 int /*<<< orphan*/  device_release_driver (int /*<<< orphan*/ *) ; 

void pnp_release_card_device(struct pnp_dev *dev)
{
	struct pnp_card_driver *drv = dev->card_link->driver;

	drv->link.remove = &card_remove;
	device_release_driver(&dev->dev);
	drv->link.remove = &card_remove_first;
}
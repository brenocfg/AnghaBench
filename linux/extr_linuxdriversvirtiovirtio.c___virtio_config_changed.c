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
struct virtio_driver {int /*<<< orphan*/  (* config_changed ) (struct virtio_device*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;
struct virtio_device {int config_change_pending; int /*<<< orphan*/  config_enabled; TYPE_1__ dev; } ;

/* Variables and functions */
 struct virtio_driver* drv_to_virtio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 

__attribute__((used)) static void __virtio_config_changed(struct virtio_device *dev)
{
	struct virtio_driver *drv = drv_to_virtio(dev->dev.driver);

	if (!dev->config_enabled)
		dev->config_change_pending = true;
	else if (drv && drv->config_changed)
		drv->config_changed(dev);
}
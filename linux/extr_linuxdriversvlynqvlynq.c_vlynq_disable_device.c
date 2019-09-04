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
struct TYPE_2__ {struct plat_vlynq_ops* platform_data; } ;
struct vlynq_device {int /*<<< orphan*/  irq; scalar_t__ enabled; TYPE_1__ dev; } ;
struct plat_vlynq_ops {int /*<<< orphan*/  (* off ) (struct vlynq_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct vlynq_device*) ; 
 int /*<<< orphan*/  stub1 (struct vlynq_device*) ; 

void vlynq_disable_device(struct vlynq_device *dev)
{
	struct plat_vlynq_ops *ops = dev->dev.platform_data;

	dev->enabled = 0;
	free_irq(dev->irq, dev);
	ops->off(dev);
}
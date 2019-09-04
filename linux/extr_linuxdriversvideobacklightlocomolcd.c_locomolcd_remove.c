#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct locomo_dev {int dummy; } ;
struct TYPE_5__ {scalar_t__ power; scalar_t__ brightness; } ;
struct TYPE_6__ {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  backlight_device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_2__* locomolcd_bl_device ; 
 int /*<<< orphan*/ * locomolcd_dev ; 
 int /*<<< orphan*/  locomolcd_set_intensity (TYPE_2__*) ; 

__attribute__((used)) static int locomolcd_remove(struct locomo_dev *dev)
{
	unsigned long flags;

	locomolcd_bl_device->props.brightness = 0;
	locomolcd_bl_device->props.power = 0;
	locomolcd_set_intensity(locomolcd_bl_device);

	backlight_device_unregister(locomolcd_bl_device);
	local_irq_save(flags);
	locomolcd_dev = NULL;
	local_irq_restore(flags);
	return 0;
}
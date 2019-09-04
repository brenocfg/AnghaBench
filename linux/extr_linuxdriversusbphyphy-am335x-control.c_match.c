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
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/ * driver; struct device_node* of_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 TYPE_1__ am335x_control_driver ; 

__attribute__((used)) static int match(struct device *dev, void *data)
{
	struct device_node *node = (struct device_node *)data;
	return dev->of_node == node &&
		dev->driver == &am335x_control_driver.driver;
}
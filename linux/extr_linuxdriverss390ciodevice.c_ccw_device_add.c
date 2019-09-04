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
struct device {int /*<<< orphan*/ * bus; } ;
struct ccw_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccw_bus_type ; 
 int device_add (struct device*) ; 

__attribute__((used)) static int ccw_device_add(struct ccw_device *cdev)
{
	struct device *dev = &cdev->dev;

	dev->bus = &ccw_bus_type;
	return device_add(dev);
}
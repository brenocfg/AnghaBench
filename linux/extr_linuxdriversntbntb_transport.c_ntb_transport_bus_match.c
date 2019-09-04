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
struct device_driver {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ntb_transport_bus_match(struct device *dev,
				   struct device_driver *drv)
{
	return !strncmp(dev_name(dev), drv->name, strlen(drv->name));
}
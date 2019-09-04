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
struct device_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_attr_version ; 
 int driver_create_file (struct device_driver*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int asd_create_driver_attrs(struct device_driver *driver)
{
	return driver_create_file(driver, &driver_attr_version);
}
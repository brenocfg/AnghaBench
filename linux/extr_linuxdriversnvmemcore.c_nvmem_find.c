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
struct nvmem_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* bus_find_device_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  nvmem_bus_type ; 
 struct nvmem_device* to_nvmem_device (struct device*) ; 

__attribute__((used)) static struct nvmem_device *nvmem_find(const char *name)
{
	struct device *d;

	d = bus_find_device_by_name(&nvmem_bus_type, NULL, name);

	if (!d)
		return NULL;

	return to_nvmem_device(d);
}
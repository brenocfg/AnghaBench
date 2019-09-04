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
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmem_bus_type ; 
 int /*<<< orphan*/  of_nvmem_match ; 
 struct nvmem_device* to_nvmem_device (struct device*) ; 

__attribute__((used)) static struct nvmem_device *of_nvmem_find(struct device_node *nvmem_np)
{
	struct device *d;

	if (!nvmem_np)
		return NULL;

	d = bus_find_device(&nvmem_bus_type, NULL, nvmem_np, of_nvmem_match);

	if (!d)
		return NULL;

	return to_nvmem_device(d);
}
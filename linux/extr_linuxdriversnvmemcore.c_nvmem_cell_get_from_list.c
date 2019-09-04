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
struct nvmem_cell {int dummy; } ;

/* Variables and functions */
 struct nvmem_cell* ERR_CAST (struct nvmem_device*) ; 
 scalar_t__ IS_ERR (struct nvmem_device*) ; 
 struct nvmem_device* __nvmem_device_get (int /*<<< orphan*/ *,struct nvmem_cell**,char const*) ; 

__attribute__((used)) static struct nvmem_cell *nvmem_cell_get_from_list(const char *cell_id)
{
	struct nvmem_cell *cell = NULL;
	struct nvmem_device *nvmem;

	nvmem = __nvmem_device_get(NULL, &cell, cell_id);
	if (IS_ERR(nvmem))
		return ERR_CAST(nvmem);

	return cell;
}
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
struct nvmem_device {int flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  eeprom; int /*<<< orphan*/  base_dev; scalar_t__ users; } ;

/* Variables and functions */
 int EBUSY ; 
 int FLAG_COMPAT ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_bin_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmem_device_remove_all_cells (struct nvmem_device*) ; 
 int /*<<< orphan*/  nvmem_mutex ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

int nvmem_unregister(struct nvmem_device *nvmem)
{
	mutex_lock(&nvmem_mutex);
	if (nvmem->users) {
		mutex_unlock(&nvmem_mutex);
		return -EBUSY;
	}
	mutex_unlock(&nvmem_mutex);

	if (nvmem->flags & FLAG_COMPAT)
		device_remove_bin_file(nvmem->base_dev, &nvmem->eeprom);

	nvmem_device_remove_all_cells(nvmem);
	device_del(&nvmem->dev);
	put_device(&nvmem->dev);

	return 0;
}
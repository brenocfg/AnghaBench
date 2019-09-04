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
struct TYPE_5__ {char* name; } ;
struct TYPE_6__ {int /*<<< orphan*/ * private; int /*<<< orphan*/  size; TYPE_1__ attr; } ;
struct nvmem_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; TYPE_2__ eeprom; scalar_t__ base_dev; int /*<<< orphan*/  size; scalar_t__ read_only; } ;
struct nvmem_config {scalar_t__ base_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FLAG_COMPAT ; 
 TYPE_2__ bin_attr_ro_root_nvmem ; 
 TYPE_2__ bin_attr_rw_root_nvmem ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int device_create_bin_file (scalar_t__,TYPE_2__*) ; 

__attribute__((used)) static int nvmem_setup_compat(struct nvmem_device *nvmem,
			      const struct nvmem_config *config)
{
	int rval;

	if (!config->base_dev)
		return -EINVAL;

	if (nvmem->read_only)
		nvmem->eeprom = bin_attr_ro_root_nvmem;
	else
		nvmem->eeprom = bin_attr_rw_root_nvmem;
	nvmem->eeprom.attr.name = "eeprom";
	nvmem->eeprom.size = nvmem->size;
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	nvmem->eeprom.attr.key = &eeprom_lock_key;
#endif
	nvmem->eeprom.private = &nvmem->dev;
	nvmem->base_dev = config->base_dev;

	rval = device_create_bin_file(nvmem->base_dev, &nvmem->eeprom);
	if (rval) {
		dev_err(&nvmem->dev,
			"Failed to create eeprom binary file %d\n", rval);
		return rval;
	}

	nvmem->flags |= FLAG_COMPAT;

	return 0;
}
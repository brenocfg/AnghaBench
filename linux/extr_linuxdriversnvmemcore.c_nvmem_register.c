#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  groups; int /*<<< orphan*/  of_node; TYPE_3__* parent; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * type; } ;
struct nvmem_device {int id; int stride; int word_size; int read_only; TYPE_2__ dev; int /*<<< orphan*/  eeprom; int /*<<< orphan*/  base_dev; int /*<<< orphan*/  reg_write; int /*<<< orphan*/  reg_read; int /*<<< orphan*/  type; int /*<<< orphan*/  priv; int /*<<< orphan*/  size; scalar_t__ owner; } ;
struct nvmem_config {int id; int read_only; scalar_t__ compat; int /*<<< orphan*/  ncells; int /*<<< orphan*/  cells; scalar_t__ name; scalar_t__ root_only; TYPE_3__* dev; int /*<<< orphan*/  reg_write; int /*<<< orphan*/  reg_read; int /*<<< orphan*/  type; int /*<<< orphan*/  priv; int /*<<< orphan*/  size; scalar_t__ word_size; scalar_t__ stride; scalar_t__ owner; } ;
struct TYPE_11__ {int /*<<< orphan*/  of_node; TYPE_1__* driver; } ;
struct TYPE_9__ {scalar_t__ owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct nvmem_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,char*,...) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_del (TYPE_2__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int device_property_present (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  device_remove_bin_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvmem_device*) ; 
 struct nvmem_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nvmem_add_cells (struct nvmem_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmem_bus_type ; 
 int /*<<< orphan*/  nvmem_ida ; 
 int /*<<< orphan*/  nvmem_provider_type ; 
 int /*<<< orphan*/  nvmem_ro_dev_groups ; 
 int /*<<< orphan*/  nvmem_ro_root_dev_groups ; 
 int /*<<< orphan*/  nvmem_rw_dev_groups ; 
 int /*<<< orphan*/  nvmem_rw_root_dev_groups ; 
 int nvmem_setup_compat (struct nvmem_device*,struct nvmem_config const*) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 

struct nvmem_device *nvmem_register(const struct nvmem_config *config)
{
	struct nvmem_device *nvmem;
	int rval;

	if (!config->dev)
		return ERR_PTR(-EINVAL);

	nvmem = kzalloc(sizeof(*nvmem), GFP_KERNEL);
	if (!nvmem)
		return ERR_PTR(-ENOMEM);

	rval  = ida_simple_get(&nvmem_ida, 0, 0, GFP_KERNEL);
	if (rval < 0) {
		kfree(nvmem);
		return ERR_PTR(rval);
	}

	nvmem->id = rval;
	nvmem->owner = config->owner;
	if (!nvmem->owner && config->dev->driver)
		nvmem->owner = config->dev->driver->owner;
	nvmem->stride = config->stride ?: 1;
	nvmem->word_size = config->word_size ?: 1;
	nvmem->size = config->size;
	nvmem->dev.type = &nvmem_provider_type;
	nvmem->dev.bus = &nvmem_bus_type;
	nvmem->dev.parent = config->dev;
	nvmem->priv = config->priv;
	nvmem->type = config->type;
	nvmem->reg_read = config->reg_read;
	nvmem->reg_write = config->reg_write;
	nvmem->dev.of_node = config->dev->of_node;

	if (config->id == -1 && config->name) {
		dev_set_name(&nvmem->dev, "%s", config->name);
	} else {
		dev_set_name(&nvmem->dev, "%s%d",
			     config->name ? : "nvmem",
			     config->name ? config->id : nvmem->id);
	}

	nvmem->read_only = device_property_present(config->dev, "read-only") |
			   config->read_only;

	if (config->root_only)
		nvmem->dev.groups = nvmem->read_only ?
			nvmem_ro_root_dev_groups :
			nvmem_rw_root_dev_groups;
	else
		nvmem->dev.groups = nvmem->read_only ?
			nvmem_ro_dev_groups :
			nvmem_rw_dev_groups;

	device_initialize(&nvmem->dev);

	dev_dbg(&nvmem->dev, "Registering nvmem device %s\n", config->name);

	rval = device_add(&nvmem->dev);
	if (rval)
		goto err_put_device;

	if (config->compat) {
		rval = nvmem_setup_compat(nvmem, config);
		if (rval)
			goto err_device_del;
	}

	if (config->cells) {
		rval = nvmem_add_cells(nvmem, config->cells, config->ncells);
		if (rval)
			goto err_teardown_compat;
	}

	return nvmem;

err_teardown_compat:
	if (config->compat)
		device_remove_bin_file(nvmem->base_dev, &nvmem->eeprom);
err_device_del:
	device_del(&nvmem->dev);
err_put_device:
	put_device(&nvmem->dev);

	return ERR_PTR(rval);
}
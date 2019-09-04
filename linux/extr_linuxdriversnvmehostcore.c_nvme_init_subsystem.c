#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  groups; int /*<<< orphan*/  release; int /*<<< orphan*/  class; } ;
struct nvme_subsystem {int instance; int cmic; TYPE_2__ dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  ctrls; int /*<<< orphan*/  entry; int /*<<< orphan*/  ns_ida; int /*<<< orphan*/  subnqn; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  firmware_rev; int /*<<< orphan*/  model; int /*<<< orphan*/  serial; int /*<<< orphan*/  nsheads; int /*<<< orphan*/  ref; } ;
struct nvme_id_ctrl {int cmic; int /*<<< orphan*/  vid; int /*<<< orphan*/  fr; int /*<<< orphan*/  mn; int /*<<< orphan*/  sn; } ;
struct nvme_ctrl {int /*<<< orphan*/  subsys_entry; TYPE_6__* device; struct nvme_subsystem* subsys; TYPE_1__* opts; } ;
struct TYPE_10__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_8__ {scalar_t__ discovery_nqn; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nvme_subsystem* __nvme_find_get_subsystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __nvme_release_subsystem (struct nvme_subsystem*) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_6__*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int) ; 
 int device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_2__*) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvme_subsystem*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct nvme_subsystem* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nvme_active_ctrls (struct nvme_subsystem*) ; 
 int /*<<< orphan*/  nvme_init_subnqn (struct nvme_subsystem*,struct nvme_ctrl*,struct nvme_id_ctrl*) ; 
 int /*<<< orphan*/  nvme_put_subsystem (struct nvme_subsystem*) ; 
 int /*<<< orphan*/  nvme_release_subsystem ; 
 int /*<<< orphan*/  nvme_subsys_attrs_groups ; 
 int /*<<< orphan*/  nvme_subsys_class ; 
 int /*<<< orphan*/  nvme_subsystems ; 
 int /*<<< orphan*/  nvme_subsystems_ida ; 
 int /*<<< orphan*/  nvme_subsystems_lock ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 scalar_t__ sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvme_init_subsystem(struct nvme_ctrl *ctrl, struct nvme_id_ctrl *id)
{
	struct nvme_subsystem *subsys, *found;
	int ret;

	subsys = kzalloc(sizeof(*subsys), GFP_KERNEL);
	if (!subsys)
		return -ENOMEM;
	ret = ida_simple_get(&nvme_subsystems_ida, 0, 0, GFP_KERNEL);
	if (ret < 0) {
		kfree(subsys);
		return ret;
	}
	subsys->instance = ret;
	mutex_init(&subsys->lock);
	kref_init(&subsys->ref);
	INIT_LIST_HEAD(&subsys->ctrls);
	INIT_LIST_HEAD(&subsys->nsheads);
	nvme_init_subnqn(subsys, ctrl, id);
	memcpy(subsys->serial, id->sn, sizeof(subsys->serial));
	memcpy(subsys->model, id->mn, sizeof(subsys->model));
	memcpy(subsys->firmware_rev, id->fr, sizeof(subsys->firmware_rev));
	subsys->vendor_id = le16_to_cpu(id->vid);
	subsys->cmic = id->cmic;

	subsys->dev.class = nvme_subsys_class;
	subsys->dev.release = nvme_release_subsystem;
	subsys->dev.groups = nvme_subsys_attrs_groups;
	dev_set_name(&subsys->dev, "nvme-subsys%d", subsys->instance);
	device_initialize(&subsys->dev);

	mutex_lock(&nvme_subsystems_lock);
	found = __nvme_find_get_subsystem(subsys->subnqn);
	if (found) {
		/*
		 * Verify that the subsystem actually supports multiple
		 * controllers, else bail out.
		 */
		if (!(ctrl->opts && ctrl->opts->discovery_nqn) &&
		    nvme_active_ctrls(found) && !(id->cmic & (1 << 1))) {
			dev_err(ctrl->device,
				"ignoring ctrl due to duplicate subnqn (%s).\n",
				found->subnqn);
			nvme_put_subsystem(found);
			ret = -EINVAL;
			goto out_unlock;
		}

		__nvme_release_subsystem(subsys);
		subsys = found;
	} else {
		ret = device_add(&subsys->dev);
		if (ret) {
			dev_err(ctrl->device,
				"failed to register subsystem device.\n");
			goto out_unlock;
		}
		ida_init(&subsys->ns_ida);
		list_add_tail(&subsys->entry, &nvme_subsystems);
	}

	ctrl->subsys = subsys;
	mutex_unlock(&nvme_subsystems_lock);

	if (sysfs_create_link(&subsys->dev.kobj, &ctrl->device->kobj,
			dev_name(ctrl->device))) {
		dev_err(ctrl->device,
			"failed to create sysfs link from subsystem.\n");
		/* the transport driver will eventually put the subsystem */
		return -EINVAL;
	}

	mutex_lock(&subsys->lock);
	list_add_tail(&ctrl->subsys_entry, &subsys->ctrls);
	mutex_unlock(&subsys->lock);

	return 0;

out_unlock:
	mutex_unlock(&nvme_subsystems_lock);
	put_device(&subsys->dev);
	return ret;
}
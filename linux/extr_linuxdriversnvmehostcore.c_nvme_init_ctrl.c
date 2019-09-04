#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct nvme_ctrl_ops {int /*<<< orphan*/  module; } ;
struct TYPE_17__ {int /*<<< orphan*/  owner; } ;
struct TYPE_13__ {int /*<<< orphan*/  set_latency_tolerance; } ;
struct TYPE_16__ {TYPE_2__ power; int /*<<< orphan*/  release; int /*<<< orphan*/  groups; struct device* parent; int /*<<< orphan*/  class; int /*<<< orphan*/  devt; } ;
struct TYPE_12__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_15__ {TYPE_1__ common; } ;
struct nvme_ctrl {unsigned long quirks; int instance; TYPE_5__* device; TYPE_9__ cdev; struct device* dev; TYPE_5__ ctrl_device; TYPE_4__ ka_cmd; int /*<<< orphan*/  ka_work; int /*<<< orphan*/  delete_work; int /*<<< orphan*/  fw_act_work; int /*<<< orphan*/  async_event_work; int /*<<< orphan*/  scan_work; struct nvme_ctrl_ops const* ops; int /*<<< orphan*/  namespaces_rwsem; int /*<<< orphan*/  namespaces; int /*<<< orphan*/  scan_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct device {TYPE_3__ kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NVME_CTRL_NEW ; 
 scalar_t__ S32_MAX ; 
 int cdev_device_add (TYPE_9__*,TYPE_5__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_ps_max_latency_us ; 
 int /*<<< orphan*/  dev_pm_qos_update_user_latency_tolerance (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_5__*,struct nvme_ctrl*) ; 
 int dev_set_name (TYPE_5__*,char*,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_5__*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_admin_keep_alive ; 
 int /*<<< orphan*/  nvme_async_event_work ; 
 int /*<<< orphan*/  nvme_chr_devt ; 
 int /*<<< orphan*/  nvme_class ; 
 int /*<<< orphan*/  nvme_delete_ctrl_work ; 
 int /*<<< orphan*/  nvme_dev_attr_groups ; 
 int /*<<< orphan*/  nvme_dev_fops ; 
 int /*<<< orphan*/  nvme_free_ctrl ; 
 int /*<<< orphan*/  nvme_fw_act_work ; 
 int /*<<< orphan*/  nvme_instance_ida ; 
 int /*<<< orphan*/  nvme_keep_alive_work ; 
 int /*<<< orphan*/  nvme_scan_work ; 
 int /*<<< orphan*/  nvme_set_latency_tolerance ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int nvme_init_ctrl(struct nvme_ctrl *ctrl, struct device *dev,
		const struct nvme_ctrl_ops *ops, unsigned long quirks)
{
	int ret;

	ctrl->state = NVME_CTRL_NEW;
	spin_lock_init(&ctrl->lock);
	mutex_init(&ctrl->scan_lock);
	INIT_LIST_HEAD(&ctrl->namespaces);
	init_rwsem(&ctrl->namespaces_rwsem);
	ctrl->dev = dev;
	ctrl->ops = ops;
	ctrl->quirks = quirks;
	INIT_WORK(&ctrl->scan_work, nvme_scan_work);
	INIT_WORK(&ctrl->async_event_work, nvme_async_event_work);
	INIT_WORK(&ctrl->fw_act_work, nvme_fw_act_work);
	INIT_WORK(&ctrl->delete_work, nvme_delete_ctrl_work);

	INIT_DELAYED_WORK(&ctrl->ka_work, nvme_keep_alive_work);
	memset(&ctrl->ka_cmd, 0, sizeof(ctrl->ka_cmd));
	ctrl->ka_cmd.common.opcode = nvme_admin_keep_alive;

	ret = ida_simple_get(&nvme_instance_ida, 0, 0, GFP_KERNEL);
	if (ret < 0)
		goto out;
	ctrl->instance = ret;

	device_initialize(&ctrl->ctrl_device);
	ctrl->device = &ctrl->ctrl_device;
	ctrl->device->devt = MKDEV(MAJOR(nvme_chr_devt), ctrl->instance);
	ctrl->device->class = nvme_class;
	ctrl->device->parent = ctrl->dev;
	ctrl->device->groups = nvme_dev_attr_groups;
	ctrl->device->release = nvme_free_ctrl;
	dev_set_drvdata(ctrl->device, ctrl);
	ret = dev_set_name(ctrl->device, "nvme%d", ctrl->instance);
	if (ret)
		goto out_release_instance;

	cdev_init(&ctrl->cdev, &nvme_dev_fops);
	ctrl->cdev.owner = ops->module;
	ret = cdev_device_add(&ctrl->cdev, ctrl->device);
	if (ret)
		goto out_free_name;

	/*
	 * Initialize latency tolerance controls.  The sysfs files won't
	 * be visible to userspace unless the device actually supports APST.
	 */
	ctrl->device->power.set_latency_tolerance = nvme_set_latency_tolerance;
	dev_pm_qos_update_user_latency_tolerance(ctrl->device,
		min(default_ps_max_latency_us, (unsigned long)S32_MAX));

	return 0;
out_free_name:
	kfree_const(dev->kobj.name);
out_release_instance:
	ida_simple_remove(&nvme_instance_ida, ctrl->instance);
out:
	return ret;
}
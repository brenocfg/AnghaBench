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
struct nvme_ns {int lba_shift; scalar_t__ ncap; int* vs; TYPE_2__* queue; int /*<<< orphan*/  siblings; struct gendisk* disk; scalar_t__ ndev; int /*<<< orphan*/  list; int /*<<< orphan*/  kref; struct nvme_ctrl* ctrl; } ;
struct nvme_id_ns {int lba_shift; scalar_t__ ncap; int* vs; TYPE_2__* queue; int /*<<< orphan*/  siblings; struct gendisk* disk; scalar_t__ ndev; int /*<<< orphan*/  list; int /*<<< orphan*/  kref; struct nvme_ctrl* ctrl; } ;
struct nvme_ctrl {int quirks; TYPE_1__* subsys; int /*<<< orphan*/  device; int /*<<< orphan*/  namespaces_rwsem; int /*<<< orphan*/  namespaces; int /*<<< orphan*/  tagset; int /*<<< orphan*/  dev; } ;
struct gendisk {int flags; int /*<<< orphan*/  disk_name; TYPE_2__* queue; struct nvme_ns* private_data; int /*<<< orphan*/ * fops; } ;
struct TYPE_11__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_10__ {struct nvme_ns* queuedata; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int DISK_NAME_LEN ; 
 int GENHD_FL_EXT_DEVT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int NVME_QUIRK_LIGHTNVM ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 int /*<<< orphan*/  __nvme_revalidate_disk (struct gendisk*,struct nvme_ns*) ; 
 struct gendisk* alloc_disk_node (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  blk_cleanup_queue (TYPE_2__*) ; 
 TYPE_2__* blk_mq_init_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (TYPE_2__*,int) ; 
 int dev_to_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_add_disk (int /*<<< orphan*/ ,struct gendisk*) ; 
 TYPE_3__* disk_to_dev (struct gendisk*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nvme_ns*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct nvme_ns* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_fault_inject_init (struct nvme_ns*) ; 
 int /*<<< orphan*/  nvme_fops ; 
 int /*<<< orphan*/  nvme_get_ctrl (struct nvme_ctrl*) ; 
 struct nvme_ns* nvme_identify_ns (struct nvme_ctrl*,unsigned int) ; 
 scalar_t__ nvme_init_ns_head (struct nvme_ns*,unsigned int,struct nvme_ns*) ; 
 int /*<<< orphan*/  nvme_mpath_add_disk (struct nvme_ns*,struct nvme_ns*) ; 
 int /*<<< orphan*/  nvme_ns_id_attr_group ; 
 scalar_t__ nvme_nvm_register (struct nvme_ns*,char*,int) ; 
 scalar_t__ nvme_nvm_register_sysfs (struct nvme_ns*) ; 
 int /*<<< orphan*/  nvme_set_disk_name (char*,struct nvme_ns*,struct nvme_ctrl*,int*) ; 
 int /*<<< orphan*/  nvme_set_queue_limits (struct nvme_ctrl*,TYPE_2__*) ; 
 int /*<<< orphan*/  nvme_setup_streams_ns (struct nvme_ctrl*,struct nvme_ns*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_alloc_ns(struct nvme_ctrl *ctrl, unsigned nsid)
{
	struct nvme_ns *ns;
	struct gendisk *disk;
	struct nvme_id_ns *id;
	char disk_name[DISK_NAME_LEN];
	int node = dev_to_node(ctrl->dev), flags = GENHD_FL_EXT_DEVT;

	ns = kzalloc_node(sizeof(*ns), GFP_KERNEL, node);
	if (!ns)
		return;

	ns->queue = blk_mq_init_queue(ctrl->tagset);
	if (IS_ERR(ns->queue))
		goto out_free_ns;
	blk_queue_flag_set(QUEUE_FLAG_NONROT, ns->queue);
	ns->queue->queuedata = ns;
	ns->ctrl = ctrl;

	kref_init(&ns->kref);
	ns->lba_shift = 9; /* set to a default value for 512 until disk is validated */

	blk_queue_logical_block_size(ns->queue, 1 << ns->lba_shift);
	nvme_set_queue_limits(ctrl, ns->queue);

	id = nvme_identify_ns(ctrl, nsid);
	if (!id)
		goto out_free_queue;

	if (id->ncap == 0)
		goto out_free_id;

	if (nvme_init_ns_head(ns, nsid, id))
		goto out_free_id;
	nvme_setup_streams_ns(ctrl, ns);
	nvme_set_disk_name(disk_name, ns, ctrl, &flags);

	if ((ctrl->quirks & NVME_QUIRK_LIGHTNVM) && id->vs[0] == 0x1) {
		if (nvme_nvm_register(ns, disk_name, node)) {
			dev_warn(ctrl->device, "LightNVM init failure\n");
			goto out_unlink_ns;
		}
	}

	disk = alloc_disk_node(0, node);
	if (!disk)
		goto out_unlink_ns;

	disk->fops = &nvme_fops;
	disk->private_data = ns;
	disk->queue = ns->queue;
	disk->flags = flags;
	memcpy(disk->disk_name, disk_name, DISK_NAME_LEN);
	ns->disk = disk;

	__nvme_revalidate_disk(disk, id);

	down_write(&ctrl->namespaces_rwsem);
	list_add_tail(&ns->list, &ctrl->namespaces);
	up_write(&ctrl->namespaces_rwsem);

	nvme_get_ctrl(ctrl);

	device_add_disk(ctrl->device, ns->disk);
	if (sysfs_create_group(&disk_to_dev(ns->disk)->kobj,
					&nvme_ns_id_attr_group))
		pr_warn("%s: failed to create sysfs group for identification\n",
			ns->disk->disk_name);
	if (ns->ndev && nvme_nvm_register_sysfs(ns))
		pr_warn("%s: failed to register lightnvm sysfs group for identification\n",
			ns->disk->disk_name);

	nvme_mpath_add_disk(ns, id);
	nvme_fault_inject_init(ns);
	kfree(id);

	return;
 out_unlink_ns:
	mutex_lock(&ctrl->subsys->lock);
	list_del_rcu(&ns->siblings);
	mutex_unlock(&ctrl->subsys->lock);
 out_free_id:
	kfree(id);
 out_free_queue:
	blk_cleanup_queue(ns->queue);
 out_free_ns:
	kfree(ns);
}
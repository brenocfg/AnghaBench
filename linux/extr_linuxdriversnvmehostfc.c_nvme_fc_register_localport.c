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
struct nvme_fc_port_template {int /*<<< orphan*/  dma_boundary; scalar_t__ local_priv_sz; int /*<<< orphan*/  max_dif_sgl_segments; int /*<<< orphan*/  max_sgl_segments; int /*<<< orphan*/  max_hw_queues; int /*<<< orphan*/  fcp_abort; int /*<<< orphan*/  ls_abort; int /*<<< orphan*/  fcp_io; int /*<<< orphan*/  ls_req; int /*<<< orphan*/  remoteport_delete; int /*<<< orphan*/  localport_delete; } ;
struct nvme_fc_port_info {int /*<<< orphan*/  port_id; int /*<<< orphan*/  port_role; int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; } ;
struct nvme_fc_local_port {int port_num; int /*<<< orphan*/  port_state; int /*<<< orphan*/  port_id; int /*<<< orphan*/  port_role; int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; struct nvme_fc_lport* private; } ;
struct nvme_fc_lport {struct nvme_fc_local_port localport; int /*<<< orphan*/  port_list; int /*<<< orphan*/  endp_cnt; struct device* dev; struct nvme_fc_port_template* ops; int /*<<< orphan*/  act_rport_cnt; int /*<<< orphan*/  ref; int /*<<< orphan*/  endp_list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FC_OBJSTATE_ONLINE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct nvme_fc_lport*) ; 
 int PTR_ERR (struct nvme_fc_lport*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_seg_boundary (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct nvme_fc_lport*) ; 
 struct nvme_fc_lport* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nvme_fc_lport* nvme_fc_attach_to_unreg_lport (struct nvme_fc_port_info*,struct nvme_fc_port_template*,struct device*) ; 
 int /*<<< orphan*/  nvme_fc_local_port_cnt ; 
 int /*<<< orphan*/  nvme_fc_lock ; 
 int /*<<< orphan*/  nvme_fc_lport_list ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
nvme_fc_register_localport(struct nvme_fc_port_info *pinfo,
			struct nvme_fc_port_template *template,
			struct device *dev,
			struct nvme_fc_local_port **portptr)
{
	struct nvme_fc_lport *newrec;
	unsigned long flags;
	int ret, idx;

	if (!template->localport_delete || !template->remoteport_delete ||
	    !template->ls_req || !template->fcp_io ||
	    !template->ls_abort || !template->fcp_abort ||
	    !template->max_hw_queues || !template->max_sgl_segments ||
	    !template->max_dif_sgl_segments || !template->dma_boundary) {
		ret = -EINVAL;
		goto out_reghost_failed;
	}

	/*
	 * look to see if there is already a localport that had been
	 * deregistered and in the process of waiting for all the
	 * references to fully be removed.  If the references haven't
	 * expired, we can simply re-enable the localport. Remoteports
	 * and controller reconnections should resume naturally.
	 */
	newrec = nvme_fc_attach_to_unreg_lport(pinfo, template, dev);

	/* found an lport, but something about its state is bad */
	if (IS_ERR(newrec)) {
		ret = PTR_ERR(newrec);
		goto out_reghost_failed;

	/* found existing lport, which was resumed */
	} else if (newrec) {
		*portptr = &newrec->localport;
		return 0;
	}

	/* nothing found - allocate a new localport struct */

	newrec = kmalloc((sizeof(*newrec) + template->local_priv_sz),
			 GFP_KERNEL);
	if (!newrec) {
		ret = -ENOMEM;
		goto out_reghost_failed;
	}

	idx = ida_simple_get(&nvme_fc_local_port_cnt, 0, 0, GFP_KERNEL);
	if (idx < 0) {
		ret = -ENOSPC;
		goto out_fail_kfree;
	}

	if (!get_device(dev) && dev) {
		ret = -ENODEV;
		goto out_ida_put;
	}

	INIT_LIST_HEAD(&newrec->port_list);
	INIT_LIST_HEAD(&newrec->endp_list);
	kref_init(&newrec->ref);
	atomic_set(&newrec->act_rport_cnt, 0);
	newrec->ops = template;
	newrec->dev = dev;
	ida_init(&newrec->endp_cnt);
	newrec->localport.private = &newrec[1];
	newrec->localport.node_name = pinfo->node_name;
	newrec->localport.port_name = pinfo->port_name;
	newrec->localport.port_role = pinfo->port_role;
	newrec->localport.port_id = pinfo->port_id;
	newrec->localport.port_state = FC_OBJSTATE_ONLINE;
	newrec->localport.port_num = idx;

	spin_lock_irqsave(&nvme_fc_lock, flags);
	list_add_tail(&newrec->port_list, &nvme_fc_lport_list);
	spin_unlock_irqrestore(&nvme_fc_lock, flags);

	if (dev)
		dma_set_seg_boundary(dev, template->dma_boundary);

	*portptr = &newrec->localport;
	return 0;

out_ida_put:
	ida_simple_remove(&nvme_fc_local_port_cnt, idx);
out_fail_kfree:
	kfree(newrec);
out_reghost_failed:
	*portptr = NULL;

	return ret;
}
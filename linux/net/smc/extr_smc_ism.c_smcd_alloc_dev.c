#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smcd_ops {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  release; struct device* parent; } ;
struct smcd_dev {struct smcd_dev* conn; int /*<<< orphan*/  event_wq; int /*<<< orphan*/  vlan; int /*<<< orphan*/  lock; int /*<<< orphan*/  pnetid; struct smcd_ops const* ops; TYPE_1__ dev; } ;
struct smc_connection {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 struct smcd_dev* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct smcd_dev*) ; 
 struct smcd_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_pnetid_by_dev_port (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smcd_release ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct smcd_dev *smcd_alloc_dev(struct device *parent, const char *name,
				const struct smcd_ops *ops, int max_dmbs)
{
	struct smcd_dev *smcd;

	smcd = kzalloc(sizeof(*smcd), GFP_KERNEL);
	if (!smcd)
		return NULL;
	smcd->conn = kcalloc(max_dmbs, sizeof(struct smc_connection *),
			     GFP_KERNEL);
	if (!smcd->conn) {
		kfree(smcd);
		return NULL;
	}

	smcd->dev.parent = parent;
	smcd->dev.release = smcd_release;
	device_initialize(&smcd->dev);
	dev_set_name(&smcd->dev, name);
	smcd->ops = ops;
	smc_pnetid_by_dev_port(parent, 0, smcd->pnetid);

	spin_lock_init(&smcd->lock);
	INIT_LIST_HEAD(&smcd->vlan);
	smcd->event_wq = alloc_ordered_workqueue("ism_evt_wq-%s)",
						 WQ_MEM_RECLAIM, name);
	if (!smcd->event_wq) {
		kfree(smcd->conn);
		kfree(smcd);
		return NULL;
	}
	return smcd;
}
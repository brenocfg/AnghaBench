#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvme_ns {int /*<<< orphan*/  disk; struct nvm_dev* ndev; } ;
struct nvm_geo {int major_ver_id; } ;
struct nvm_dev {struct nvm_geo geo; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 TYPE_1__* disk_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvm_dev_attr_group_12 ; 
 int /*<<< orphan*/  nvm_dev_attr_group_20 ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void nvme_nvm_unregister_sysfs(struct nvme_ns *ns)
{
	struct nvm_dev *ndev = ns->ndev;
	struct nvm_geo *geo = &ndev->geo;

	switch (geo->major_ver_id) {
	case 1:
		sysfs_remove_group(&disk_to_dev(ns->disk)->kobj,
					&nvm_dev_attr_group_12);
		break;
	case 2:
		sysfs_remove_group(&disk_to_dev(ns->disk)->kobj,
					&nvm_dev_attr_group_20);
		break;
	}
}
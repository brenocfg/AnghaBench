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
struct request_queue {int dummy; } ;
struct nvme_ns {struct nvm_dev* ndev; struct request_queue* queue; } ;
struct nvm_dev {struct nvme_ns* private_data; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; struct request_queue* q; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISK_NAME_LEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  _nvme_nvm_check_size () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct nvm_dev* nvm_alloc_dev (int) ; 
 int nvm_register (struct nvm_dev*) ; 
 int /*<<< orphan*/  nvme_nvm_dev_ops ; 

int nvme_nvm_register(struct nvme_ns *ns, char *disk_name, int node)
{
	struct request_queue *q = ns->queue;
	struct nvm_dev *dev;

	_nvme_nvm_check_size();

	dev = nvm_alloc_dev(node);
	if (!dev)
		return -ENOMEM;

	dev->q = q;
	memcpy(dev->name, disk_name, DISK_NAME_LEN);
	dev->ops = &nvme_nvm_dev_ops;
	dev->private_data = ns;
	ns->ndev = dev;

	return nvm_register(dev);
}
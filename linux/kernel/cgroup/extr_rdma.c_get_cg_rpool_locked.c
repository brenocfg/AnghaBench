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
struct rdmacg_resource_pool {int /*<<< orphan*/  dev_node; int /*<<< orphan*/  cg_node; struct rdmacg_device* device; } ;
struct rdmacg_device {int /*<<< orphan*/  rpools; } ;
struct rdma_cgroup {int /*<<< orphan*/  rpools; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct rdmacg_resource_pool* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct rdmacg_resource_pool* find_cg_rpool_locked (struct rdma_cgroup*,struct rdmacg_device*) ; 
 struct rdmacg_resource_pool* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_all_resource_max_limit (struct rdmacg_resource_pool*) ; 

__attribute__((used)) static struct rdmacg_resource_pool *
get_cg_rpool_locked(struct rdma_cgroup *cg, struct rdmacg_device *device)
{
	struct rdmacg_resource_pool *rpool;

	rpool = find_cg_rpool_locked(cg, device);
	if (rpool)
		return rpool;

	rpool = kzalloc(sizeof(*rpool), GFP_KERNEL);
	if (!rpool)
		return ERR_PTR(-ENOMEM);

	rpool->device = device;
	set_all_resource_max_limit(rpool);

	INIT_LIST_HEAD(&rpool->cg_node);
	INIT_LIST_HEAD(&rpool->dev_node);
	list_add_tail(&rpool->cg_node, &cg->rpools);
	list_add_tail(&rpool->dev_node, &device->rpools);
	return rpool;
}
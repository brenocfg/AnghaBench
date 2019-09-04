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
struct rdmacg_resource_pool {int /*<<< orphan*/  usage_sum; TYPE_1__* resources; } ;
struct rdmacg_device {int dummy; } ;
struct rdma_cgroup {int dummy; } ;
typedef  scalar_t__ s64 ;
typedef  enum rdmacg_resource_type { ____Placeholder_rdmacg_resource_type } rdmacg_resource_type ;
struct TYPE_2__ {scalar_t__ usage; scalar_t__ max; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct rdmacg_resource_pool*) ; 
 int PTR_ERR (struct rdmacg_resource_pool*) ; 
 int RDMACG_RESOURCE_MAX ; 
 struct rdmacg_resource_pool* get_cg_rpool_locked (struct rdma_cgroup*,struct rdmacg_device*) ; 
 struct rdma_cgroup* get_current_rdmacg () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rdma_cgroup* parent_rdmacg (struct rdma_cgroup*) ; 
 int /*<<< orphan*/  rdmacg_mutex ; 
 int /*<<< orphan*/  rdmacg_uncharge_hierarchy (struct rdma_cgroup*,struct rdmacg_device*,struct rdma_cgroup*,int) ; 

int rdmacg_try_charge(struct rdma_cgroup **rdmacg,
		      struct rdmacg_device *device,
		      enum rdmacg_resource_type index)
{
	struct rdma_cgroup *cg, *p;
	struct rdmacg_resource_pool *rpool;
	s64 new;
	int ret = 0;

	if (index >= RDMACG_RESOURCE_MAX)
		return -EINVAL;

	/*
	 * hold on to css, as cgroup can be removed but resource
	 * accounting happens on css.
	 */
	cg = get_current_rdmacg();

	mutex_lock(&rdmacg_mutex);
	for (p = cg; p; p = parent_rdmacg(p)) {
		rpool = get_cg_rpool_locked(p, device);
		if (IS_ERR(rpool)) {
			ret = PTR_ERR(rpool);
			goto err;
		} else {
			new = rpool->resources[index].usage + 1;
			if (new > rpool->resources[index].max) {
				ret = -EAGAIN;
				goto err;
			} else {
				rpool->resources[index].usage = new;
				rpool->usage_sum++;
			}
		}
	}
	mutex_unlock(&rdmacg_mutex);

	*rdmacg = cg;
	return 0;

err:
	mutex_unlock(&rdmacg_mutex);
	rdmacg_uncharge_hierarchy(cg, device, p, index);
	return ret;
}
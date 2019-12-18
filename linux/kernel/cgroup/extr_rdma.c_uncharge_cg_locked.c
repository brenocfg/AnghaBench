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
struct rdmacg_resource_pool {scalar_t__ usage_sum; scalar_t__ num_max_cnt; TYPE_1__* resources; } ;
struct rdmacg_device {int dummy; } ;
struct rdma_cgroup {int dummy; } ;
typedef  enum rdmacg_resource_type { ____Placeholder_rdmacg_resource_type } rdmacg_resource_type ;
struct TYPE_2__ {scalar_t__ usage; } ;

/* Variables and functions */
 scalar_t__ RDMACG_RESOURCE_MAX ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct rdmacg_resource_pool* find_cg_rpool_locked (struct rdma_cgroup*,struct rdmacg_device*) ; 
 int /*<<< orphan*/  free_cg_rpool_locked (struct rdmacg_resource_pool*) ; 
 int /*<<< orphan*/  pr_warn (char*,struct rdma_cgroup*,struct rdmacg_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
uncharge_cg_locked(struct rdma_cgroup *cg,
		   struct rdmacg_device *device,
		   enum rdmacg_resource_type index)
{
	struct rdmacg_resource_pool *rpool;

	rpool = find_cg_rpool_locked(cg, device);

	/*
	 * rpool cannot be null at this stage. Let kernel operate in case
	 * if there a bug in IB stack or rdma controller, instead of crashing
	 * the system.
	 */
	if (unlikely(!rpool)) {
		pr_warn("Invalid device %p or rdma cgroup %p\n", cg, device);
		return;
	}

	rpool->resources[index].usage--;

	/*
	 * A negative count (or overflow) is invalid,
	 * it indicates a bug in the rdma controller.
	 */
	WARN_ON_ONCE(rpool->resources[index].usage < 0);
	rpool->usage_sum--;
	if (rpool->usage_sum == 0 &&
	    rpool->num_max_cnt == RDMACG_RESOURCE_MAX) {
		/*
		 * No user of the rpool and all entries are set to max, so
		 * safe to delete this rpool.
		 */
		free_cg_rpool_locked(rpool);
	}
}
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
struct rdmacg_device {int dummy; } ;
struct rdma_cgroup {int /*<<< orphan*/  css; } ;
typedef  enum rdmacg_resource_type { ____Placeholder_rdmacg_resource_type } rdmacg_resource_type ;

/* Variables and functions */
 int /*<<< orphan*/  css_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rdma_cgroup* parent_rdmacg (struct rdma_cgroup*) ; 
 int /*<<< orphan*/  rdmacg_mutex ; 
 int /*<<< orphan*/  uncharge_cg_locked (struct rdma_cgroup*,struct rdmacg_device*,int) ; 

__attribute__((used)) static void rdmacg_uncharge_hierarchy(struct rdma_cgroup *cg,
				     struct rdmacg_device *device,
				     struct rdma_cgroup *stop_cg,
				     enum rdmacg_resource_type index)
{
	struct rdma_cgroup *p;

	mutex_lock(&rdmacg_mutex);

	for (p = cg; p != stop_cg; p = parent_rdmacg(p))
		uncharge_cg_locked(p, device, index);

	mutex_unlock(&rdmacg_mutex);

	css_put(&cg->css);
}
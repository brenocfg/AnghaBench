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
struct rdma_cgroup {int dummy; } ;
typedef  enum rdmacg_resource_type { ____Placeholder_rdmacg_resource_type } rdmacg_resource_type ;

/* Variables and functions */
 int RDMACG_RESOURCE_MAX ; 
 int /*<<< orphan*/  rdmacg_uncharge_hierarchy (struct rdma_cgroup*,struct rdmacg_device*,int /*<<< orphan*/ *,int) ; 

void rdmacg_uncharge(struct rdma_cgroup *cg,
		     struct rdmacg_device *device,
		     enum rdmacg_resource_type index)
{
	if (index >= RDMACG_RESOURCE_MAX)
		return;

	rdmacg_uncharge_hierarchy(cg, device, NULL, index);
}
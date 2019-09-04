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
struct nvme_ns {scalar_t__ disk; } ;
struct nvme_ctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_alloc_ns (struct nvme_ctrl*,unsigned int) ; 
 struct nvme_ns* nvme_find_get_ns (struct nvme_ctrl*,unsigned int) ; 
 int /*<<< orphan*/  nvme_ns_remove (struct nvme_ns*) ; 
 int /*<<< orphan*/  nvme_put_ns (struct nvme_ns*) ; 
 scalar_t__ revalidate_disk (scalar_t__) ; 

__attribute__((used)) static void nvme_validate_ns(struct nvme_ctrl *ctrl, unsigned nsid)
{
	struct nvme_ns *ns;

	ns = nvme_find_get_ns(ctrl, nsid);
	if (ns) {
		if (ns->disk && revalidate_disk(ns->disk))
			nvme_ns_remove(ns);
		nvme_put_ns(ns);
	} else
		nvme_alloc_ns(ctrl, nsid);
}
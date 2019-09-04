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
struct nvme_ns_head {int /*<<< orphan*/  srcu; int /*<<< orphan*/  current_path; } ;
struct nvme_ns {int dummy; } ;

/* Variables and functions */
 struct nvme_ns* __nvme_find_path (struct nvme_ns_head*) ; 
 int /*<<< orphan*/  nvme_path_is_optimized (struct nvme_ns*) ; 
 struct nvme_ns* srcu_dereference (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

inline struct nvme_ns *nvme_find_path(struct nvme_ns_head *head)
{
	struct nvme_ns *ns = srcu_dereference(head->current_path, &head->srcu);

	if (unlikely(!ns || !nvme_path_is_optimized(ns)))
		ns = __nvme_find_path(head);
	return ns;
}
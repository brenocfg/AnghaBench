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
struct nvmet_ns {int /*<<< orphan*/  ref; } ;
struct nvmet_ctrl {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 struct nvmet_ns* __nvmet_find_namespace (struct nvmet_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_ref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct nvmet_ns *nvmet_find_namespace(struct nvmet_ctrl *ctrl, __le32 nsid)
{
	struct nvmet_ns *ns;

	rcu_read_lock();
	ns = __nvmet_find_namespace(ctrl, nsid);
	if (ns)
		percpu_ref_get(&ns->ref);
	rcu_read_unlock();

	return ns;
}
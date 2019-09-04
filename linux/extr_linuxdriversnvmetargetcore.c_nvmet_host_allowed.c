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
struct nvmet_subsys {scalar_t__ type; } ;
struct nvmet_req {int dummy; } ;

/* Variables and functions */
 scalar_t__ NVME_NQN_DISC ; 
 int __nvmet_host_allowed (struct nvmet_subsys*,char const*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_config_sem ; 
 int nvmet_host_discovery_allowed (struct nvmet_req*,char const*) ; 

bool nvmet_host_allowed(struct nvmet_req *req, struct nvmet_subsys *subsys,
		const char *hostnqn)
{
	lockdep_assert_held(&nvmet_config_sem);

	if (subsys->type == NVME_NQN_DISC)
		return nvmet_host_discovery_allowed(req, hostnqn);
	else
		return __nvmet_host_allowed(subsys, hostnqn);
}
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
typedef  int u32 ;
struct nvmet_ns {int anagrpid; int /*<<< orphan*/  subsys; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int NVMET_MAX_ANAGRPS ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int kstrtou32 (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  nvmet_ana_chgcnt ; 
 int /*<<< orphan*/ * nvmet_ana_group_enabled ; 
 int /*<<< orphan*/  nvmet_ana_sem ; 
 int /*<<< orphan*/  nvmet_send_ana_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nvmet_ns* to_nvmet_ns (struct config_item*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t nvmet_ns_ana_grpid_store(struct config_item *item,
		const char *page, size_t count)
{
	struct nvmet_ns *ns = to_nvmet_ns(item);
	u32 oldgrpid, newgrpid;
	int ret;

	ret = kstrtou32(page, 0, &newgrpid);
	if (ret)
		return ret;

	if (newgrpid < 1 || newgrpid > NVMET_MAX_ANAGRPS)
		return -EINVAL;

	down_write(&nvmet_ana_sem);
	oldgrpid = ns->anagrpid;
	nvmet_ana_group_enabled[newgrpid]++;
	ns->anagrpid = newgrpid;
	nvmet_ana_group_enabled[oldgrpid]--;
	nvmet_ana_chgcnt++;
	up_write(&nvmet_ana_sem);

	nvmet_send_ana_event(ns->subsys, NULL);
	return count;
}
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
typedef  scalar_t__ u32 ;
struct nvme_ctrl {TYPE_1__* device; scalar_t__ aen_result; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static void nvme_aen_uevent(struct nvme_ctrl *ctrl)
{
	char *envp[2] = { NULL, NULL };
	u32 aen_result = ctrl->aen_result;

	ctrl->aen_result = 0;
	if (!aen_result)
		return;

	envp[0] = kasprintf(GFP_KERNEL, "NVME_AEN=%#08x", aen_result);
	if (!envp[0])
		return;
	kobject_uevent_env(&ctrl->device->kobj, KOBJ_CHANGE, envp);
	kfree(envp[0]);
}
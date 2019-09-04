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
struct nvmet_ns {size_t anagrpid; struct nvmet_ns* device_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nvmet_ns*) ; 
 int /*<<< orphan*/ * nvmet_ana_group_enabled ; 
 int /*<<< orphan*/  nvmet_ana_sem ; 
 int /*<<< orphan*/  nvmet_ns_disable (struct nvmet_ns*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void nvmet_ns_free(struct nvmet_ns *ns)
{
	nvmet_ns_disable(ns);

	down_write(&nvmet_ana_sem);
	nvmet_ana_group_enabled[ns->anagrpid]--;
	up_write(&nvmet_ana_sem);

	kfree(ns->device_path);
	kfree(ns);
}
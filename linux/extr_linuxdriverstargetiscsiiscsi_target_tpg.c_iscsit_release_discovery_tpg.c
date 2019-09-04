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
struct iscsi_portal_group {int /*<<< orphan*/  tpg_se_tpg; int /*<<< orphan*/  param_list; } ;
struct TYPE_2__ {struct iscsi_portal_group* discovery_tpg; } ;

/* Variables and functions */
 int /*<<< orphan*/  core_tpg_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_release_param_list (int /*<<< orphan*/ ) ; 
 TYPE_1__* iscsit_global ; 
 int /*<<< orphan*/  kfree (struct iscsi_portal_group*) ; 

void iscsit_release_discovery_tpg(void)
{
	struct iscsi_portal_group *tpg = iscsit_global->discovery_tpg;

	if (!tpg)
		return;

	iscsi_release_param_list(tpg->param_list);
	core_tpg_deregister(&tpg->tpg_se_tpg);

	kfree(tpg);
	iscsit_global->discovery_tpg = NULL;
}
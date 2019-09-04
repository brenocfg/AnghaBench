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
struct iscsi_tpg_np {TYPE_1__* tpg_np; } ;
struct iscsi_portal_group {int dummy; } ;
struct TYPE_2__ {int enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsit_reset_np_thread (TYPE_1__*,struct iscsi_tpg_np*,struct iscsi_portal_group*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void iscsit_clear_tpg_np_login_thread(
	struct iscsi_tpg_np *tpg_np,
	struct iscsi_portal_group *tpg,
	bool shutdown)
{
	if (!tpg_np->tpg_np) {
		pr_err("struct iscsi_tpg_np->tpg_np is NULL!\n");
		return;
	}

	if (shutdown)
		tpg_np->tpg_np->enabled = false;
	iscsit_reset_np_thread(tpg_np->tpg_np, tpg_np, tpg, shutdown);
}
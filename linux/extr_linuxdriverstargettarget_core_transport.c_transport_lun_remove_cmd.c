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
struct se_lun {int /*<<< orphan*/  lun_ref; } ;
struct se_cmd {int /*<<< orphan*/  lun_ref_active; struct se_lun* se_lun; } ;

/* Variables and functions */
 scalar_t__ cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  percpu_ref_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void transport_lun_remove_cmd(struct se_cmd *cmd)
{
	struct se_lun *lun = cmd->se_lun;

	if (!lun)
		return;

	if (cmpxchg(&cmd->lun_ref_active, true, false))
		percpu_ref_put(&lun->lun_ref);
}
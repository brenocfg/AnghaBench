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
struct tb {int /*<<< orphan*/  nhi; int /*<<< orphan*/ * root_switch; } ;
struct icm {int /*<<< orphan*/  rescan_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  NHI_MAILBOX_DRV_UNLOADS ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nhi_mailbox_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct icm* tb_priv (struct tb*) ; 
 int /*<<< orphan*/  tb_switch_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void icm_stop(struct tb *tb)
{
	struct icm *icm = tb_priv(tb);

	cancel_delayed_work(&icm->rescan_work);
	tb_switch_remove(tb->root_switch);
	tb->root_switch = NULL;
	nhi_mailbox_cmd(tb->nhi, NHI_MAILBOX_DRV_UNLOADS, 0);
}
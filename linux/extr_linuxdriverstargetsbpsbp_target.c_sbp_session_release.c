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
struct sbp_session {scalar_t__ card; int /*<<< orphan*/  se_sess; int /*<<< orphan*/  maint_work; int /*<<< orphan*/  lock; int /*<<< orphan*/  login_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_card_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct sbp_session*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_remove_session (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sbp_session_release(struct sbp_session *sess, bool cancel_work)
{
	spin_lock_bh(&sess->lock);
	if (!list_empty(&sess->login_list)) {
		spin_unlock_bh(&sess->lock);
		return;
	}
	spin_unlock_bh(&sess->lock);

	if (cancel_work)
		cancel_delayed_work_sync(&sess->maint_work);

	target_remove_session(sess->se_sess);

	if (sess->card)
		fw_card_put(sess->card);

	kfree(sess);
}
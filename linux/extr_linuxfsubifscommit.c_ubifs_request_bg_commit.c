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
struct ubifs_info {scalar_t__ cmt_state; int /*<<< orphan*/  cs_lock; } ;

/* Variables and functions */
 scalar_t__ COMMIT_BACKGROUND ; 
 scalar_t__ COMMIT_RESTING ; 
 int /*<<< orphan*/  dbg_cmt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_cstate (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_wake_up_bgt (struct ubifs_info*) ; 

void ubifs_request_bg_commit(struct ubifs_info *c)
{
	spin_lock(&c->cs_lock);
	if (c->cmt_state == COMMIT_RESTING) {
		dbg_cmt("old: %s, new: %s", dbg_cstate(c->cmt_state),
			dbg_cstate(COMMIT_BACKGROUND));
		c->cmt_state = COMMIT_BACKGROUND;
		spin_unlock(&c->cs_lock);
		ubifs_wake_up_bgt(c);
	} else
		spin_unlock(&c->cs_lock);
}
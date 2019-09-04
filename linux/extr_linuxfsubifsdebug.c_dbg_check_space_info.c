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
struct ubifs_lp_stats {int dummy; } ;
struct ubifs_info {int freeable_cnt; int /*<<< orphan*/  bi; int /*<<< orphan*/  space_lock; struct ubifs_debug_info* dbg; } ;
struct ubifs_debug_info {long long saved_free; int /*<<< orphan*/  saved_idx_gc_cnt; int /*<<< orphan*/  saved_bi; struct ubifs_lp_stats saved_lst; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_dump_budg (struct ubifs_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_dump_lstats (struct ubifs_lp_stats*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,long long,long long) ; 
 long long ubifs_get_free_space_nolock (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_get_lp_stats (struct ubifs_info*,struct ubifs_lp_stats*) ; 
 int /*<<< orphan*/  ubifs_msg (struct ubifs_info*,char*,...) ; 

int dbg_check_space_info(struct ubifs_info *c)
{
	struct ubifs_debug_info *d = c->dbg;
	struct ubifs_lp_stats lst;
	long long free;
	int freeable_cnt;

	spin_lock(&c->space_lock);
	freeable_cnt = c->freeable_cnt;
	c->freeable_cnt = 0;
	free = ubifs_get_free_space_nolock(c);
	c->freeable_cnt = freeable_cnt;
	spin_unlock(&c->space_lock);

	if (free != d->saved_free) {
		ubifs_err(c, "free space changed from %lld to %lld",
			  d->saved_free, free);
		goto out;
	}

	return 0;

out:
	ubifs_msg(c, "saved lprops statistics dump");
	ubifs_dump_lstats(&d->saved_lst);
	ubifs_msg(c, "saved budgeting info dump");
	ubifs_dump_budg(c, &d->saved_bi);
	ubifs_msg(c, "saved idx_gc_cnt %d", d->saved_idx_gc_cnt);
	ubifs_msg(c, "current lprops statistics dump");
	ubifs_get_lp_stats(c, &lst);
	ubifs_dump_lstats(&lst);
	ubifs_msg(c, "current budgeting info dump");
	ubifs_dump_budg(c, &c->bi);
	dump_stack();
	return -EINVAL;
}
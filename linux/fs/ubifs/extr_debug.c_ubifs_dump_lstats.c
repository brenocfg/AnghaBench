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
struct ubifs_lp_stats {int /*<<< orphan*/  total_dead; int /*<<< orphan*/  total_dark; int /*<<< orphan*/  total_used; int /*<<< orphan*/  total_dirty; int /*<<< orphan*/  total_free; int /*<<< orphan*/  taken_empty_lebs; int /*<<< orphan*/  idx_lebs; int /*<<< orphan*/  empty_lebs; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  dbg_lock ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ubifs_dump_lstats(const struct ubifs_lp_stats *lst)
{
	spin_lock(&dbg_lock);
	pr_err("(pid %d) Lprops statistics: empty_lebs %d, idx_lebs  %d\n",
	       current->pid, lst->empty_lebs, lst->idx_lebs);
	pr_err("\ttaken_empty_lebs %d, total_free %lld, total_dirty %lld\n",
	       lst->taken_empty_lebs, lst->total_free, lst->total_dirty);
	pr_err("\ttotal_used %lld, total_dark %lld, total_dead %lld\n",
	       lst->total_used, lst->total_dark, lst->total_dead);
	spin_unlock(&dbg_lock);
}
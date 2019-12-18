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
struct rpc_task {int /*<<< orphan*/  tk_start; } ;
struct nfs4_ff_layout_mirror {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  read_stat; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_FF_MIRROR_STAT_AVAIL ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  nfs4_ff_layout_stat_io_update_completed (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfs4_ff_layout_stat_io_end_read(struct rpc_task *task,
		struct nfs4_ff_layout_mirror *mirror,
		__u64 requested,
		__u64 completed)
{
	spin_lock(&mirror->lock);
	nfs4_ff_layout_stat_io_update_completed(&mirror->read_stat,
			requested, completed,
			ktime_get(), task->tk_start);
	set_bit(NFS4_FF_MIRROR_STAT_AVAIL, &mirror->flags);
	spin_unlock(&mirror->lock);
}
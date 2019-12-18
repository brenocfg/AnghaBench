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
struct nfs4_ff_layout_mirror {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  read_stat; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFS4_FF_MIRROR_STAT_AVAIL ; 
 int /*<<< orphan*/  nfs4_ff_layout_stat_io_update_requested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nfs4_ff_layoutstat_start_io (struct nfs4_ff_layout_mirror*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_report_layoutstat (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfs4_ff_layout_stat_io_start_read(struct inode *inode,
		struct nfs4_ff_layout_mirror *mirror,
		__u64 requested, ktime_t now)
{
	bool report;

	spin_lock(&mirror->lock);
	report = nfs4_ff_layoutstat_start_io(mirror, &mirror->read_stat, now);
	nfs4_ff_layout_stat_io_update_requested(&mirror->read_stat, requested);
	set_bit(NFS4_FF_MIRROR_STAT_AVAIL, &mirror->flags);
	spin_unlock(&mirror->lock);

	if (report)
		pnfs_report_layoutstat(inode, GFP_KERNEL);
}
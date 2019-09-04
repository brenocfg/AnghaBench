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
struct seq_file {int dummy; } ;
struct ocfs2_super {unsigned long s_mount_opt; scalar_t__ preferred_slot; int osb_commit_interval; int local_alloc_bits; int s_clustersize_bits; int /*<<< orphan*/  osb_resv_level; int /*<<< orphan*/  osb_dir_resv_level; scalar_t__* osb_cluster_stack; int /*<<< orphan*/  s_atime_quantum; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  OCFS2_DEFAULT_RESV_LEVEL ; 
 int /*<<< orphan*/  OCFS2_HB_GLOBAL ; 
 int /*<<< orphan*/  OCFS2_HB_LOCAL ; 
 int /*<<< orphan*/  OCFS2_HB_NONE ; 
 scalar_t__ OCFS2_INVALID_SLOT ; 
 unsigned long OCFS2_MOUNT_BARRIER ; 
 unsigned long OCFS2_MOUNT_COHERENCY_BUFFERED ; 
 unsigned long OCFS2_MOUNT_DATA_WRITEBACK ; 
 unsigned long OCFS2_MOUNT_ERRORS_CONT ; 
 unsigned long OCFS2_MOUNT_ERRORS_PANIC ; 
 unsigned long OCFS2_MOUNT_GRPQUOTA ; 
 unsigned long OCFS2_MOUNT_HB_GLOBAL ; 
 unsigned long OCFS2_MOUNT_HB_LOCAL ; 
 unsigned long OCFS2_MOUNT_INODE64 ; 
 unsigned long OCFS2_MOUNT_JOURNAL_ASYNC_COMMIT ; 
 unsigned long OCFS2_MOUNT_LOCALFLOCKS ; 
 unsigned long OCFS2_MOUNT_NOINTR ; 
 unsigned long OCFS2_MOUNT_NOUSERXATTR ; 
 unsigned long OCFS2_MOUNT_POSIX_ACL ; 
 unsigned long OCFS2_MOUNT_USRQUOTA ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCFS2_STACK_LABEL_LEN ; 
 unsigned int ocfs2_la_default_mb (struct ocfs2_super*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_show_option_n (struct seq_file*,char*,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_show_options(struct seq_file *s, struct dentry *root)
{
	struct ocfs2_super *osb = OCFS2_SB(root->d_sb);
	unsigned long opts = osb->s_mount_opt;
	unsigned int local_alloc_megs;

	if (opts & (OCFS2_MOUNT_HB_LOCAL | OCFS2_MOUNT_HB_GLOBAL)) {
		seq_printf(s, ",_netdev");
		if (opts & OCFS2_MOUNT_HB_LOCAL)
			seq_printf(s, ",%s", OCFS2_HB_LOCAL);
		else
			seq_printf(s, ",%s", OCFS2_HB_GLOBAL);
	} else
		seq_printf(s, ",%s", OCFS2_HB_NONE);

	if (opts & OCFS2_MOUNT_NOINTR)
		seq_printf(s, ",nointr");

	if (opts & OCFS2_MOUNT_DATA_WRITEBACK)
		seq_printf(s, ",data=writeback");
	else
		seq_printf(s, ",data=ordered");

	if (opts & OCFS2_MOUNT_BARRIER)
		seq_printf(s, ",barrier=1");

	if (opts & OCFS2_MOUNT_ERRORS_PANIC)
		seq_printf(s, ",errors=panic");
	else if (opts & OCFS2_MOUNT_ERRORS_CONT)
		seq_printf(s, ",errors=continue");
	else
		seq_printf(s, ",errors=remount-ro");

	if (osb->preferred_slot != OCFS2_INVALID_SLOT)
		seq_printf(s, ",preferred_slot=%d", osb->preferred_slot);

	seq_printf(s, ",atime_quantum=%u", osb->s_atime_quantum);

	if (osb->osb_commit_interval)
		seq_printf(s, ",commit=%u",
			   (unsigned) (osb->osb_commit_interval / HZ));

	local_alloc_megs = osb->local_alloc_bits >> (20 - osb->s_clustersize_bits);
	if (local_alloc_megs != ocfs2_la_default_mb(osb))
		seq_printf(s, ",localalloc=%d", local_alloc_megs);

	if (opts & OCFS2_MOUNT_LOCALFLOCKS)
		seq_printf(s, ",localflocks,");

	if (osb->osb_cluster_stack[0])
		seq_show_option_n(s, "cluster_stack", osb->osb_cluster_stack,
				  OCFS2_STACK_LABEL_LEN);
	if (opts & OCFS2_MOUNT_USRQUOTA)
		seq_printf(s, ",usrquota");
	if (opts & OCFS2_MOUNT_GRPQUOTA)
		seq_printf(s, ",grpquota");

	if (opts & OCFS2_MOUNT_COHERENCY_BUFFERED)
		seq_printf(s, ",coherency=buffered");
	else
		seq_printf(s, ",coherency=full");

	if (opts & OCFS2_MOUNT_NOUSERXATTR)
		seq_printf(s, ",nouser_xattr");
	else
		seq_printf(s, ",user_xattr");

	if (opts & OCFS2_MOUNT_INODE64)
		seq_printf(s, ",inode64");

	if (opts & OCFS2_MOUNT_POSIX_ACL)
		seq_printf(s, ",acl");
	else
		seq_printf(s, ",noacl");

	if (osb->osb_resv_level != OCFS2_DEFAULT_RESV_LEVEL)
		seq_printf(s, ",resv_level=%d", osb->osb_resv_level);

	if (osb->osb_dir_resv_level != osb->osb_resv_level)
		seq_printf(s, ",dir_resv_level=%d", osb->osb_resv_level);

	if (opts & OCFS2_MOUNT_JOURNAL_ASYNC_COMMIT)
		seq_printf(s, ",journal_async_commit");

	return 0;
}
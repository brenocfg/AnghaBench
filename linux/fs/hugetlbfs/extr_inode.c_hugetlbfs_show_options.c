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
struct hugetlbfs_sb_info {int mode; int max_inodes; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  hstate; struct hugepage_subpool* spool; } ;
struct hugepage_subpool {int max_hpages; int min_hpages; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 struct hugetlbfs_sb_info* HUGETLBFS_SB (int /*<<< orphan*/ ) ; 
 unsigned long long from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long long from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int huge_page_shift (int /*<<< orphan*/ ) ; 
 unsigned long huge_page_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned long long,...) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hugetlbfs_show_options(struct seq_file *m, struct dentry *root)
{
	struct hugetlbfs_sb_info *sbinfo = HUGETLBFS_SB(root->d_sb);
	struct hugepage_subpool *spool = sbinfo->spool;
	unsigned long hpage_size = huge_page_size(sbinfo->hstate);
	unsigned hpage_shift = huge_page_shift(sbinfo->hstate);
	char mod;

	if (!uid_eq(sbinfo->uid, GLOBAL_ROOT_UID))
		seq_printf(m, ",uid=%u",
			   from_kuid_munged(&init_user_ns, sbinfo->uid));
	if (!gid_eq(sbinfo->gid, GLOBAL_ROOT_GID))
		seq_printf(m, ",gid=%u",
			   from_kgid_munged(&init_user_ns, sbinfo->gid));
	if (sbinfo->mode != 0755)
		seq_printf(m, ",mode=%o", sbinfo->mode);
	if (sbinfo->max_inodes != -1)
		seq_printf(m, ",nr_inodes=%lu", sbinfo->max_inodes);

	hpage_size /= 1024;
	mod = 'K';
	if (hpage_size >= 1024) {
		hpage_size /= 1024;
		mod = 'M';
	}
	seq_printf(m, ",pagesize=%lu%c", hpage_size, mod);
	if (spool) {
		if (spool->max_hpages != -1)
			seq_printf(m, ",size=%llu",
				   (unsigned long long)spool->max_hpages << hpage_shift);
		if (spool->min_hpages != -1)
			seq_printf(m, ",min_size=%llu",
				   (unsigned long long)spool->min_hpages << hpage_shift);
	}
	return 0;
}
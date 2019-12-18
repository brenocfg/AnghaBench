#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * files; } ;
struct super_block {TYPE_1__ s_dquot; } ;
struct ocfs2_super {struct super_block* sb; } ;
struct ocfs2_mem_dqinfo {int /*<<< orphan*/  dqi_sync_work; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {struct ocfs2_mem_dqinfo* dqi_priv; } ;

/* Variables and functions */
 int DQUOT_LIMITS_ENABLED ; 
 int DQUOT_USAGE_ENABLED ; 
 int OCFS2_MAXQUOTAS ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dquot_disable (struct super_block*,int,int) ; 
 struct inode* igrab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 TYPE_2__* sb_dqinfo (struct super_block*,int) ; 
 int /*<<< orphan*/  sb_has_quota_loaded (struct super_block*,int) ; 

__attribute__((used)) static void ocfs2_disable_quotas(struct ocfs2_super *osb)
{
	int type;
	struct inode *inode;
	struct super_block *sb = osb->sb;
	struct ocfs2_mem_dqinfo *oinfo;

	/* We mostly ignore errors in this function because there's not much
	 * we can do when we see them */
	for (type = 0; type < OCFS2_MAXQUOTAS; type++) {
		if (!sb_has_quota_loaded(sb, type))
			continue;
		oinfo = sb_dqinfo(sb, type)->dqi_priv;
		cancel_delayed_work_sync(&oinfo->dqi_sync_work);
		inode = igrab(sb->s_dquot.files[type]);
		/* Turn off quotas. This will remove all dquot structures from
		 * memory and so they will be automatically synced to global
		 * quota files */
		dquot_disable(sb, type, DQUOT_USAGE_ENABLED |
					DQUOT_LIMITS_ENABLED);
		if (!inode)
			continue;
		iput(inode);
	}
}
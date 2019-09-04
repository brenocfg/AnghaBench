#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_3__* s_op; } ;
struct qtree_mem_dqinfo {int dqi_entry_size; TYPE_2__* dqi_ops; } ;
struct TYPE_4__ {int type; } ;
struct dquot {int /*<<< orphan*/  dq_off; int /*<<< orphan*/  dq_dqb_lock; struct super_block* dq_sb; TYPE_1__ dq_id; } ;
typedef  int ssize_t ;
struct TYPE_6__ {int (* quota_write ) (struct super_block*,int,char*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* mem2disk_dqblk ) (char*,struct dquot*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DQST_WRITES ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int dq_insert_tree (struct qtree_mem_dqinfo*,struct dquot*) ; 
 int /*<<< orphan*/  dqstats_inc (int /*<<< orphan*/ ) ; 
 char* getdqbuf (int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  quota_error (struct super_block*,char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (char*,struct dquot*) ; 
 int stub2 (struct super_block*,int,char*,int,int /*<<< orphan*/ ) ; 

int qtree_write_dquot(struct qtree_mem_dqinfo *info, struct dquot *dquot)
{
	int type = dquot->dq_id.type;
	struct super_block *sb = dquot->dq_sb;
	ssize_t ret;
	char *ddquot = getdqbuf(info->dqi_entry_size);

	if (!ddquot)
		return -ENOMEM;

	/* dq_off is guarded by dqio_sem */
	if (!dquot->dq_off) {
		ret = dq_insert_tree(info, dquot);
		if (ret < 0) {
			quota_error(sb, "Error %zd occurred while creating "
				    "quota", ret);
			kfree(ddquot);
			return ret;
		}
	}
	spin_lock(&dquot->dq_dqb_lock);
	info->dqi_ops->mem2disk_dqblk(ddquot, dquot);
	spin_unlock(&dquot->dq_dqb_lock);
	ret = sb->s_op->quota_write(sb, type, ddquot, info->dqi_entry_size,
				    dquot->dq_off);
	if (ret != info->dqi_entry_size) {
		quota_error(sb, "dquota write failed");
		if (ret >= 0)
			ret = -ENOSPC;
	} else {
		ret = 0;
	}
	dqstats_inc(DQST_WRITES);
	kfree(ddquot);

	return ret;
}
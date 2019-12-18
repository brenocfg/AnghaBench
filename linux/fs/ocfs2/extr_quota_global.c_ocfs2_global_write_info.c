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
struct super_block {int dummy; } ;
struct quota_info {int /*<<< orphan*/  dqio_sem; TYPE_1__* info; } ;
struct ocfs2_mem_dqinfo {int dummy; } ;
struct TYPE_2__ {struct ocfs2_mem_dqinfo* dqi_priv; } ;

/* Variables and functions */
 int __ocfs2_global_write_info (struct super_block*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int ocfs2_qinfo_lock (struct ocfs2_mem_dqinfo*,int) ; 
 int /*<<< orphan*/  ocfs2_qinfo_unlock (struct ocfs2_mem_dqinfo*,int) ; 
 struct quota_info* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ocfs2_global_write_info(struct super_block *sb, int type)
{
	int err;
	struct quota_info *dqopt = sb_dqopt(sb);
	struct ocfs2_mem_dqinfo *info = dqopt->info[type].dqi_priv;

	down_write(&dqopt->dqio_sem);
	err = ocfs2_qinfo_lock(info, 1);
	if (err < 0)
		goto out_sem;
	err = __ocfs2_global_write_info(sb, type);
	ocfs2_qinfo_unlock(info, 1);
out_sem:
	up_write(&dqopt->dqio_sem);
	return err;
}
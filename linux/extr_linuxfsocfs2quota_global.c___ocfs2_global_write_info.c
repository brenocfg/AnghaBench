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
struct super_block {TYPE_2__* s_op; } ;
struct TYPE_3__ {int /*<<< orphan*/  dqi_free_entry; int /*<<< orphan*/  dqi_free_blk; int /*<<< orphan*/  dqi_blocks; } ;
struct ocfs2_mem_dqinfo {TYPE_1__ dqi_gi; int /*<<< orphan*/  dqi_syncms; } ;
struct ocfs2_global_disk_dqinfo {void* dqi_free_entry; void* dqi_free_blk; void* dqi_blocks; void* dqi_syncms; void* dqi_igrace; void* dqi_bgrace; } ;
struct mem_dqinfo {int /*<<< orphan*/  dqi_igrace; int /*<<< orphan*/  dqi_bgrace; int /*<<< orphan*/  dqi_flags; struct ocfs2_mem_dqinfo* dqi_priv; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int (* quota_write ) (struct super_block*,int,char*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DQF_INFO_DIRTY ; 
 int EIO ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  OCFS2_GLOBAL_INFO_OFF ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 struct mem_dqinfo* sb_dqinfo (struct super_block*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct super_block*,int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ocfs2_global_write_info(struct super_block *sb, int type)
{
	struct mem_dqinfo *info = sb_dqinfo(sb, type);
	struct ocfs2_mem_dqinfo *oinfo = info->dqi_priv;
	struct ocfs2_global_disk_dqinfo dinfo;
	ssize_t size;

	spin_lock(&dq_data_lock);
	info->dqi_flags &= ~DQF_INFO_DIRTY;
	dinfo.dqi_bgrace = cpu_to_le32(info->dqi_bgrace);
	dinfo.dqi_igrace = cpu_to_le32(info->dqi_igrace);
	spin_unlock(&dq_data_lock);
	dinfo.dqi_syncms = cpu_to_le32(oinfo->dqi_syncms);
	dinfo.dqi_blocks = cpu_to_le32(oinfo->dqi_gi.dqi_blocks);
	dinfo.dqi_free_blk = cpu_to_le32(oinfo->dqi_gi.dqi_free_blk);
	dinfo.dqi_free_entry = cpu_to_le32(oinfo->dqi_gi.dqi_free_entry);
	size = sb->s_op->quota_write(sb, type, (char *)&dinfo,
				     sizeof(struct ocfs2_global_disk_dqinfo),
				     OCFS2_GLOBAL_INFO_OFF);
	if (size != sizeof(struct ocfs2_global_disk_dqinfo)) {
		mlog(ML_ERROR, "Cannot write global quota info structure\n");
		if (size >= 0)
			size = -EIO;
		return size;
	}
	return 0;
}
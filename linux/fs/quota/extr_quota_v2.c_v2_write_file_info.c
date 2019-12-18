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
struct v2_disk_dqinfo {void* dqi_free_entry; void* dqi_free_blk; void* dqi_blocks; void* dqi_flags; void* dqi_igrace; void* dqi_bgrace; } ;
struct super_block {TYPE_1__* s_op; } ;
struct quota_info {int /*<<< orphan*/  dqio_sem; struct mem_dqinfo* info; } ;
struct qtree_mem_dqinfo {int /*<<< orphan*/  dqi_free_entry; int /*<<< orphan*/  dqi_free_blk; int /*<<< orphan*/  dqi_blocks; } ;
struct mem_dqinfo {int /*<<< orphan*/  dqi_igrace; int /*<<< orphan*/  dqi_bgrace; int /*<<< orphan*/  dqi_flags; struct qtree_mem_dqinfo* dqi_priv; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* quota_write ) (struct super_block*,int,char*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DQF_INFO_DIRTY ; 
 int /*<<< orphan*/  V2_DQINFOOFF ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int /*<<< orphan*/  quota_error (struct super_block*,char*) ; 
 struct quota_info* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct super_block*,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int v2_write_file_info(struct super_block *sb, int type)
{
	struct v2_disk_dqinfo dinfo;
	struct quota_info *dqopt = sb_dqopt(sb);
	struct mem_dqinfo *info = &dqopt->info[type];
	struct qtree_mem_dqinfo *qinfo = info->dqi_priv;
	ssize_t size;

	down_write(&dqopt->dqio_sem);
	spin_lock(&dq_data_lock);
	info->dqi_flags &= ~DQF_INFO_DIRTY;
	dinfo.dqi_bgrace = cpu_to_le32(info->dqi_bgrace);
	dinfo.dqi_igrace = cpu_to_le32(info->dqi_igrace);
	/* No flags currently supported */
	dinfo.dqi_flags = cpu_to_le32(0);
	spin_unlock(&dq_data_lock);
	dinfo.dqi_blocks = cpu_to_le32(qinfo->dqi_blocks);
	dinfo.dqi_free_blk = cpu_to_le32(qinfo->dqi_free_blk);
	dinfo.dqi_free_entry = cpu_to_le32(qinfo->dqi_free_entry);
	size = sb->s_op->quota_write(sb, type, (char *)&dinfo,
	       sizeof(struct v2_disk_dqinfo), V2_DQINFOOFF);
	up_write(&dqopt->dqio_sem);
	if (size != sizeof(struct v2_disk_dqinfo)) {
		quota_error(sb, "Can't write info structure");
		return -1;
	}
	return 0;
}
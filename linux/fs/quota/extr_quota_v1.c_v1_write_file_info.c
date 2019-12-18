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
struct v1_disk_dqblk {int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_itime; } ;
struct super_block {TYPE_2__* s_op; } ;
struct quota_info {int /*<<< orphan*/  dqio_sem; TYPE_1__* info; } ;
struct TYPE_4__ {int (* quota_read ) (struct super_block*,int,char*,int,int /*<<< orphan*/ ) ;int (* quota_write ) (struct super_block*,int,char*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dqi_bgrace; int /*<<< orphan*/  dqi_igrace; int /*<<< orphan*/  dqi_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DQF_INFO_DIRTY ; 
 int EIO ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dq_data_lock ; 
 struct quota_info* sb_dqopt (struct super_block*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct super_block*,int,char*,int,int /*<<< orphan*/ ) ; 
 int stub2 (struct super_block*,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v1_dqoff (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int v1_write_file_info(struct super_block *sb, int type)
{
	struct quota_info *dqopt = sb_dqopt(sb);
	struct v1_disk_dqblk dqblk;
	int ret;

	down_write(&dqopt->dqio_sem);
	ret = sb->s_op->quota_read(sb, type, (char *)&dqblk,
				sizeof(struct v1_disk_dqblk), v1_dqoff(0));
	if (ret != sizeof(struct v1_disk_dqblk)) {
		if (ret >= 0)
			ret = -EIO;
		goto out;
	}
	spin_lock(&dq_data_lock);
	dqopt->info[type].dqi_flags &= ~DQF_INFO_DIRTY;
	dqblk.dqb_itime = dqopt->info[type].dqi_igrace;
	dqblk.dqb_btime = dqopt->info[type].dqi_bgrace;
	spin_unlock(&dq_data_lock);
	ret = sb->s_op->quota_write(sb, type, (char *)&dqblk,
	      sizeof(struct v1_disk_dqblk), v1_dqoff(0));
	if (ret == sizeof(struct v1_disk_dqblk))
		ret = 0;
	else if (ret > 0)
		ret = -EIO;
out:
	up_write(&dqopt->dqio_sem);
	return ret;
}
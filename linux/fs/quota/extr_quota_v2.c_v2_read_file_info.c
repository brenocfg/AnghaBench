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
struct v2r1_disk_dqblk {int dummy; } ;
struct v2r0_disk_dqblk {int dummy; } ;
struct v2_disk_dqinfo {int /*<<< orphan*/  dqi_free_entry; int /*<<< orphan*/  dqi_free_blk; int /*<<< orphan*/  dqi_blocks; int /*<<< orphan*/  dqi_igrace; int /*<<< orphan*/  dqi_bgrace; } ;
struct v2_disk_dqheader {int /*<<< orphan*/  dqh_version; } ;
struct super_block {TYPE_1__* s_op; } ;
struct quota_info {int /*<<< orphan*/  dqio_sem; struct mem_dqinfo* info; } ;
struct qtree_mem_dqinfo {int dqi_type; int dqi_blocksize_bits; int dqi_usable_bs; int dqi_entry_size; int /*<<< orphan*/ * dqi_ops; int /*<<< orphan*/  dqi_qtree_depth; void* dqi_free_entry; void* dqi_free_blk; void* dqi_blocks; struct super_block* dqi_sb; } ;
struct mem_dqinfo {scalar_t__ dqi_fmt_id; int dqi_max_spc_limit; int dqi_max_ino_limit; scalar_t__ dqi_flags; void* dqi_igrace; void* dqi_bgrace; struct qtree_mem_dqinfo* dqi_priv; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* quota_read ) (struct super_block*,int,char*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ QFMT_VFS_V0 ; 
 scalar_t__ QFMT_VFS_V1 ; 
 int QUOTABLOCK_BITS ; 
 int V2_DQBLKSIZE_BITS ; 
 int /*<<< orphan*/  V2_DQINFOOFF ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct qtree_mem_dqinfo* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtree_depth (struct qtree_mem_dqinfo*) ; 
 int /*<<< orphan*/  quota_error (struct super_block*,char*) ; 
 struct quota_info* sb_dqopt (struct super_block*) ; 
 int stub1 (struct super_block*,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int v2_read_header (struct super_block*,int,struct v2_disk_dqheader*) ; 
 int /*<<< orphan*/  v2r0_qtree_ops ; 
 int /*<<< orphan*/  v2r1_qtree_ops ; 

__attribute__((used)) static int v2_read_file_info(struct super_block *sb, int type)
{
	struct v2_disk_dqinfo dinfo;
	struct v2_disk_dqheader dqhead;
	struct quota_info *dqopt = sb_dqopt(sb);
	struct mem_dqinfo *info = &dqopt->info[type];
	struct qtree_mem_dqinfo *qinfo;
	ssize_t size;
	unsigned int version;
	int ret;

	down_read(&dqopt->dqio_sem);
	ret = v2_read_header(sb, type, &dqhead);
	if (ret < 0)
		goto out;
	version = le32_to_cpu(dqhead.dqh_version);
	if ((info->dqi_fmt_id == QFMT_VFS_V0 && version != 0) ||
	    (info->dqi_fmt_id == QFMT_VFS_V1 && version != 1)) {
		ret = -EINVAL;
		goto out;
	}

	size = sb->s_op->quota_read(sb, type, (char *)&dinfo,
	       sizeof(struct v2_disk_dqinfo), V2_DQINFOOFF);
	if (size != sizeof(struct v2_disk_dqinfo)) {
		quota_error(sb, "Can't read info structure");
		if (size < 0)
			ret = size;
		else
			ret = -EIO;
		goto out;
	}
	info->dqi_priv = kmalloc(sizeof(struct qtree_mem_dqinfo), GFP_NOFS);
	if (!info->dqi_priv) {
		ret = -ENOMEM;
		goto out;
	}
	qinfo = info->dqi_priv;
	if (version == 0) {
		/* limits are stored as unsigned 32-bit data */
		info->dqi_max_spc_limit = 0xffffffffLL << QUOTABLOCK_BITS;
		info->dqi_max_ino_limit = 0xffffffff;
	} else {
		/*
		 * Used space is stored as unsigned 64-bit value in bytes but
		 * quota core supports only signed 64-bit values so use that
		 * as a limit
		 */
		info->dqi_max_spc_limit = 0x7fffffffffffffffLL; /* 2^63-1 */
		info->dqi_max_ino_limit = 0x7fffffffffffffffLL;
	}
	info->dqi_bgrace = le32_to_cpu(dinfo.dqi_bgrace);
	info->dqi_igrace = le32_to_cpu(dinfo.dqi_igrace);
	/* No flags currently supported */
	info->dqi_flags = 0;
	qinfo->dqi_sb = sb;
	qinfo->dqi_type = type;
	qinfo->dqi_blocks = le32_to_cpu(dinfo.dqi_blocks);
	qinfo->dqi_free_blk = le32_to_cpu(dinfo.dqi_free_blk);
	qinfo->dqi_free_entry = le32_to_cpu(dinfo.dqi_free_entry);
	qinfo->dqi_blocksize_bits = V2_DQBLKSIZE_BITS;
	qinfo->dqi_usable_bs = 1 << V2_DQBLKSIZE_BITS;
	qinfo->dqi_qtree_depth = qtree_depth(qinfo);
	if (version == 0) {
		qinfo->dqi_entry_size = sizeof(struct v2r0_disk_dqblk);
		qinfo->dqi_ops = &v2r0_qtree_ops;
	} else {
		qinfo->dqi_entry_size = sizeof(struct v2r1_disk_dqblk);
		qinfo->dqi_ops = &v2r1_qtree_ops;
	}
	ret = 0;
out:
	up_read(&dqopt->dqio_sem);
	return ret;
}
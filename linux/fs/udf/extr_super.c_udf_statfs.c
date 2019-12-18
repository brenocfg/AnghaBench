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
typedef  int u64 ;
typedef  void* u32 ;
struct udf_sb_info {size_t s_partition; TYPE_2__* s_partmaps; } ;
struct super_block {int /*<<< orphan*/  s_blocksize; TYPE_1__* s_bdev; } ;
struct logicalVolIntegrityDescImpUse {int /*<<< orphan*/  numDirs; int /*<<< orphan*/  numFiles; } ;
struct TYPE_6__ {void** val; } ;
struct kstatfs {TYPE_3__ f_fsid; int /*<<< orphan*/  f_namelen; scalar_t__ f_bfree; scalar_t__ f_ffree; scalar_t__ f_files; scalar_t__ f_bavail; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_partition_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDF_NAME_LEN ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  UDF_SUPER_MAGIC ; 
 int huge_encode_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ udf_count_free (struct super_block*) ; 
 struct logicalVolIntegrityDescImpUse* udf_sb_lvidiu (struct super_block*) ; 

__attribute__((used)) static int udf_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *sb = dentry->d_sb;
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct logicalVolIntegrityDescImpUse *lvidiu;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	lvidiu = udf_sb_lvidiu(sb);
	buf->f_type = UDF_SUPER_MAGIC;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = sbi->s_partmaps[sbi->s_partition].s_partition_len;
	buf->f_bfree = udf_count_free(sb);
	buf->f_bavail = buf->f_bfree;
	buf->f_files = (lvidiu != NULL ? (le32_to_cpu(lvidiu->numFiles) +
					  le32_to_cpu(lvidiu->numDirs)) : 0)
			+ buf->f_bfree;
	buf->f_ffree = buf->f_bfree;
	buf->f_namelen = UDF_NAME_LEN;
	buf->f_fsid.val[0] = (u32)id;
	buf->f_fsid.val[1] = (u32)(id >> 32);

	return 0;
}
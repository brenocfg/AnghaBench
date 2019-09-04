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
typedef  int u64 ;
typedef  void* u32 ;
struct super_block {int /*<<< orphan*/  s_blocksize; TYPE_1__* s_bdev; } ;
struct TYPE_4__ {void** val; } ;
struct kstatfs {int f_blocks; int f_bfree; int f_bavail; int f_files; int /*<<< orphan*/  f_namelen; TYPE_2__ f_fsid; scalar_t__ f_ffree; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct hfsplus_sb_info {int total_blocks; int fs_shift; int free_blocks; scalar_t__ next_cnid; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFSPLUS_MAX_STRLEN ; 
 struct hfsplus_sb_info* HFSPLUS_SB (struct super_block*) ; 
 int /*<<< orphan*/  HFSPLUS_SUPER_MAGIC ; 
 int huge_encode_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hfsplus_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *sb = dentry->d_sb;
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type = HFSPLUS_SUPER_MAGIC;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = sbi->total_blocks << sbi->fs_shift;
	buf->f_bfree = sbi->free_blocks << sbi->fs_shift;
	buf->f_bavail = buf->f_bfree;
	buf->f_files = 0xFFFFFFFF;
	buf->f_ffree = 0xFFFFFFFF - sbi->next_cnid;
	buf->f_fsid.val[0] = (u32)id;
	buf->f_fsid.val[1] = (u32)(id >> 32);
	buf->f_namelen = HFSPLUS_MAX_STRLEN;

	return 0;
}
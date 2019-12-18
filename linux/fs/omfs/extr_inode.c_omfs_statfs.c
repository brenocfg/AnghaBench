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
struct super_block {TYPE_1__* s_bdev; } ;
struct omfs_sb_info {int /*<<< orphan*/  s_num_blocks; int /*<<< orphan*/  s_blocksize; } ;
struct TYPE_4__ {void** val; } ;
struct kstatfs {int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; TYPE_2__ f_fsid; int /*<<< orphan*/  f_namelen; int /*<<< orphan*/  f_files; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMFS_MAGIC ; 
 int /*<<< orphan*/  OMFS_NAMELEN ; 
 struct omfs_sb_info* OMFS_SB (struct super_block*) ; 
 int huge_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omfs_count_free (struct super_block*) ; 

__attribute__((used)) static int omfs_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *s = dentry->d_sb;
	struct omfs_sb_info *sbi = OMFS_SB(s);
	u64 id = huge_encode_dev(s->s_bdev->bd_dev);

	buf->f_type = OMFS_MAGIC;
	buf->f_bsize = sbi->s_blocksize;
	buf->f_blocks = sbi->s_num_blocks;
	buf->f_files = sbi->s_num_blocks;
	buf->f_namelen = OMFS_NAMELEN;
	buf->f_fsid.val[0] = (u32)id;
	buf->f_fsid.val[1] = (u32)(id >> 32);

	buf->f_bfree = buf->f_bavail = buf->f_ffree =
		omfs_count_free(s);

	return 0;
}
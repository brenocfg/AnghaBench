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
struct sysv_sb_info {int /*<<< orphan*/  s_ninodes; int /*<<< orphan*/  s_ndatazones; } ;
struct super_block {int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_magic; TYPE_1__* s_bdev; } ;
struct TYPE_4__ {void** val; } ;
struct kstatfs {TYPE_2__ f_fsid; int /*<<< orphan*/  f_namelen; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_files; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSV_NAMELEN ; 
 struct sysv_sb_info* SYSV_SB (struct super_block*) ; 
 int huge_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysv_count_free_blocks (struct super_block*) ; 
 int /*<<< orphan*/  sysv_count_free_inodes (struct super_block*) ; 

__attribute__((used)) static int sysv_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *sb = dentry->d_sb;
	struct sysv_sb_info *sbi = SYSV_SB(sb);
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type = sb->s_magic;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = sbi->s_ndatazones;
	buf->f_bavail = buf->f_bfree = sysv_count_free_blocks(sb);
	buf->f_files = sbi->s_ninodes;
	buf->f_ffree = sysv_count_free_inodes(sb);
	buf->f_namelen = SYSV_NAMELEN;
	buf->f_fsid.val[0] = (u32)id;
	buf->f_fsid.val[1] = (u32)(id >> 32);
	return 0;
}
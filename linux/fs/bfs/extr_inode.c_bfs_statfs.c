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
struct kstatfs {int /*<<< orphan*/  f_namelen; TYPE_2__ f_fsid; int /*<<< orphan*/  f_ffree; scalar_t__ f_files; int /*<<< orphan*/  f_bavail; int /*<<< orphan*/  f_bfree; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct dentry {struct super_block* d_sb; } ;
struct bfs_sb_info {int /*<<< orphan*/  si_freei; scalar_t__ si_lasti; int /*<<< orphan*/  si_freeb; int /*<<< orphan*/  si_blocks; } ;
struct TYPE_3__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFS_MAGIC ; 
 int /*<<< orphan*/  BFS_NAMELEN ; 
 scalar_t__ BFS_ROOT_INO ; 
 struct bfs_sb_info* BFS_SB (struct super_block*) ; 
 int huge_encode_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bfs_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *s = dentry->d_sb;
	struct bfs_sb_info *info = BFS_SB(s);
	u64 id = huge_encode_dev(s->s_bdev->bd_dev);
	buf->f_type = BFS_MAGIC;
	buf->f_bsize = s->s_blocksize;
	buf->f_blocks = info->si_blocks;
	buf->f_bfree = buf->f_bavail = info->si_freeb;
	buf->f_files = info->si_lasti + 1 - BFS_ROOT_INO;
	buf->f_ffree = info->si_freei;
	buf->f_fsid.val[0] = (u32)id;
	buf->f_fsid.val[1] = (u32)(id >> 32);
	buf->f_namelen = BFS_NAMELEN;
	return 0;
}
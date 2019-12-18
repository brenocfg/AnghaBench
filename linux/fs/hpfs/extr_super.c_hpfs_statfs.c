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
struct super_block {int /*<<< orphan*/  s_magic; TYPE_1__* s_bdev; } ;
struct TYPE_4__ {void** val; } ;
struct kstatfs {int f_bsize; unsigned int f_bfree; unsigned int f_bavail; int f_files; int f_namelen; TYPE_2__ f_fsid; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_type; } ;
struct hpfs_sb_info {unsigned int sb_n_free; int sb_dirband_size; int /*<<< orphan*/  sb_fs_size; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 unsigned int count_bitmaps (struct super_block*) ; 
 int /*<<< orphan*/  hpfs_get_free_dnodes (struct super_block*) ; 
 int /*<<< orphan*/  hpfs_lock (struct super_block*) ; 
 struct hpfs_sb_info* hpfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  hpfs_unlock (struct super_block*) ; 
 int huge_encode_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpfs_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *s = dentry->d_sb;
	struct hpfs_sb_info *sbi = hpfs_sb(s);
	u64 id = huge_encode_dev(s->s_bdev->bd_dev);

	hpfs_lock(s);

	if (sbi->sb_n_free == (unsigned)-1)
		sbi->sb_n_free = count_bitmaps(s);

	buf->f_type = s->s_magic;
	buf->f_bsize = 512;
	buf->f_blocks = sbi->sb_fs_size;
	buf->f_bfree = sbi->sb_n_free;
	buf->f_bavail = sbi->sb_n_free;
	buf->f_files = sbi->sb_dirband_size / 4;
	buf->f_ffree = hpfs_get_free_dnodes(s);
	buf->f_fsid.val[0] = (u32)id;
	buf->f_fsid.val[1] = (u32)(id >> 32);
	buf->f_namelen = 254;

	hpfs_unlock(s);

	return 0;
}
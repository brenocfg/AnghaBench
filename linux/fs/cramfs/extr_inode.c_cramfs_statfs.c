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
struct super_block {scalar_t__ s_dev; TYPE_1__* s_bdev; } ;
struct TYPE_5__ {void** val; } ;
struct kstatfs {int /*<<< orphan*/  f_namelen; TYPE_2__ f_fsid; scalar_t__ f_ffree; int /*<<< orphan*/  f_files; scalar_t__ f_bavail; scalar_t__ f_bfree; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_6__ {int /*<<< orphan*/  files; int /*<<< orphan*/  blocks; } ;
struct TYPE_4__ {scalar_t__ bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRAMFS_MAGIC ; 
 int /*<<< orphan*/  CRAMFS_MAXPATHLEN ; 
 TYPE_3__* CRAMFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int huge_encode_dev (scalar_t__) ; 

__attribute__((used)) static int cramfs_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *sb = dentry->d_sb;
	u64 id = 0;

	if (sb->s_bdev)
		id = huge_encode_dev(sb->s_bdev->bd_dev);
	else if (sb->s_dev)
		id = huge_encode_dev(sb->s_dev);

	buf->f_type = CRAMFS_MAGIC;
	buf->f_bsize = PAGE_SIZE;
	buf->f_blocks = CRAMFS_SB(sb)->blocks;
	buf->f_bfree = 0;
	buf->f_bavail = 0;
	buf->f_files = CRAMFS_SB(sb)->files;
	buf->f_ffree = 0;
	buf->f_fsid.val[0] = (u32)id;
	buf->f_fsid.val[1] = (u32)(id >> 32);
	buf->f_namelen = CRAMFS_MAXPATHLEN;
	return 0;
}
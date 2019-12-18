#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  void* u32 ;
struct TYPE_6__ {int /*<<< orphan*/  cs_nifree; } ;
struct ufs_sb_private_info {scalar_t__ s_root_blocks; int s_ncg; int s_ipg; TYPE_2__ cs_total; int /*<<< orphan*/  s_dsize; } ;
struct super_block {int /*<<< orphan*/  s_blocksize; TYPE_1__* s_bdev; } ;
struct TYPE_7__ {void** val; } ;
struct kstatfs {scalar_t__ f_bfree; scalar_t__ f_bavail; int f_files; TYPE_3__ f_fsid; int /*<<< orphan*/  f_namelen; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_ffree; int /*<<< orphan*/  f_blocks; int /*<<< orphan*/  f_type; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_8__ {unsigned int s_flags; int /*<<< orphan*/  s_lock; struct ufs_sb_private_info* s_uspi; } ;
struct TYPE_5__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UFS2_MAGIC ; 
 int /*<<< orphan*/  UFS_MAGIC ; 
 int /*<<< orphan*/  UFS_MAXNAMLEN ; 
 TYPE_4__* UFS_SB (struct super_block*) ; 
 unsigned int UFS_TYPE_MASK ; 
 unsigned int UFS_TYPE_UFS2 ; 
 int huge_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ufs_freefrags (struct ufs_sb_private_info*) ; 

__attribute__((used)) static int ufs_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *sb = dentry->d_sb;
	struct ufs_sb_private_info *uspi= UFS_SB(sb)->s_uspi;
	unsigned  flags = UFS_SB(sb)->s_flags;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	mutex_lock(&UFS_SB(sb)->s_lock);
	
	if ((flags & UFS_TYPE_MASK) == UFS_TYPE_UFS2)
		buf->f_type = UFS2_MAGIC;
	else
		buf->f_type = UFS_MAGIC;

	buf->f_blocks = uspi->s_dsize;
	buf->f_bfree = ufs_freefrags(uspi);
	buf->f_ffree = uspi->cs_total.cs_nifree;
	buf->f_bsize = sb->s_blocksize;
	buf->f_bavail = (buf->f_bfree > uspi->s_root_blocks)
		? (buf->f_bfree - uspi->s_root_blocks) : 0;
	buf->f_files = uspi->s_ncg * uspi->s_ipg;
	buf->f_namelen = UFS_MAXNAMLEN;
	buf->f_fsid.val[0] = (u32)id;
	buf->f_fsid.val[1] = (u32)(id >> 32);

	mutex_unlock(&UFS_SB(sb)->s_lock);

	return 0;
}
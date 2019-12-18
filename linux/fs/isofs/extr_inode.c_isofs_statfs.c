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
struct super_block {int s_blocksize_bits; int /*<<< orphan*/  s_blocksize; TYPE_1__* s_bdev; } ;
struct TYPE_5__ {void** val; } ;
struct kstatfs {int f_blocks; int /*<<< orphan*/  f_namelen; TYPE_2__ f_fsid; scalar_t__ f_ffree; int /*<<< orphan*/  f_files; scalar_t__ f_bavail; scalar_t__ f_bfree; int /*<<< orphan*/  f_bsize; int /*<<< orphan*/  f_type; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_6__ {int s_nzones; int s_log_zone_size; int /*<<< orphan*/  s_ninodes; } ;
struct TYPE_4__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 TYPE_3__* ISOFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  ISOFS_SUPER_MAGIC ; 
 int /*<<< orphan*/  NAME_MAX ; 
 int huge_encode_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isofs_statfs (struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *sb = dentry->d_sb;
	u64 id = huge_encode_dev(sb->s_bdev->bd_dev);

	buf->f_type = ISOFS_SUPER_MAGIC;
	buf->f_bsize = sb->s_blocksize;
	buf->f_blocks = (ISOFS_SB(sb)->s_nzones
		<< (ISOFS_SB(sb)->s_log_zone_size - sb->s_blocksize_bits));
	buf->f_bfree = 0;
	buf->f_bavail = 0;
	buf->f_files = ISOFS_SB(sb)->s_ninodes;
	buf->f_ffree = 0;
	buf->f_fsid.val[0] = (u32)id;
	buf->f_fsid.val[1] = (u32)(id >> 32);
	buf->f_namelen = NAME_MAX;
	return 0;
}
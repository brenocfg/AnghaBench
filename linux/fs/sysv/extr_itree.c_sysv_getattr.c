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
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int s_blocksize; } ;
struct path {TYPE_1__* dentry; } ;
struct kstat {int blocks; int blksize; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {struct super_block* d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (TYPE_1__*) ; 
 int /*<<< orphan*/  generic_fillattr (int /*<<< orphan*/ ,struct kstat*) ; 
 int sysv_nblocks (struct super_block*,int /*<<< orphan*/ ) ; 

int sysv_getattr(const struct path *path, struct kstat *stat,
		 u32 request_mask, unsigned int flags)
{
	struct super_block *s = path->dentry->d_sb;
	generic_fillattr(d_inode(path->dentry), stat);
	stat->blocks = (s->s_blocksize / 512) * sysv_nblocks(s, stat->size);
	stat->blksize = s->s_blocksize;
	return 0;
}
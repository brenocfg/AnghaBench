#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_root; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_maxbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLMFS_MAGIC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  d_make_root (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlmfs_get_root_inode (struct super_block*) ; 
 int /*<<< orphan*/  dlmfs_ops ; 

__attribute__((used)) static int dlmfs_fill_super(struct super_block * sb,
			    void * data,
			    int silent)
{
	sb->s_maxbytes = MAX_LFS_FILESIZE;
	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = DLMFS_MAGIC;
	sb->s_op = &dlmfs_ops;
	sb->s_root = d_make_root(dlmfs_get_root_inode(sb));
	if (!sb->s_root)
		return -ENOMEM;
	return 0;
}
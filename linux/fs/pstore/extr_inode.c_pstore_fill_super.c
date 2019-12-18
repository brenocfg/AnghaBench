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
struct super_block {int s_time_gran; int /*<<< orphan*/  s_root; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_maxbytes; } ;
struct inode {int i_mode; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PSTOREFS_MAGIC ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  parse_options (void*) ; 
 int /*<<< orphan*/  pstore_dir_inode_operations ; 
 struct inode* pstore_get_inode (struct super_block*) ; 
 int /*<<< orphan*/  pstore_get_records (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstore_ops ; 
 struct super_block* pstore_sb ; 
 int /*<<< orphan*/  simple_dir_operations ; 

__attribute__((used)) static int pstore_fill_super(struct super_block *sb, void *data, int silent)
{
	struct inode *inode;

	pstore_sb = sb;

	sb->s_maxbytes		= MAX_LFS_FILESIZE;
	sb->s_blocksize		= PAGE_SIZE;
	sb->s_blocksize_bits	= PAGE_SHIFT;
	sb->s_magic		= PSTOREFS_MAGIC;
	sb->s_op		= &pstore_ops;
	sb->s_time_gran		= 1;

	parse_options(data);

	inode = pstore_get_inode(sb);
	if (inode) {
		inode->i_mode = S_IFDIR | 0750;
		inode->i_op = &pstore_dir_inode_operations;
		inode->i_fop = &simple_dir_operations;
		inc_nlink(inode);
	}
	sb->s_root = d_make_root(inode);
	if (!sb->s_root)
		return -ENOMEM;

	pstore_get_records(0);

	return 0;
}
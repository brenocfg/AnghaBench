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
struct super_block {int s_time_gran; int /*<<< orphan*/  s_d_op; int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_xattr; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_maxbytes; } ;
struct pseudo_fs_context {int /*<<< orphan*/  dops; int /*<<< orphan*/  xattr; scalar_t__ ops; int /*<<< orphan*/  magic; } ;
struct inode {int i_ino; int i_mode; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; } ;
struct fs_context {struct pseudo_fs_context* fs_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int S_IFDIR ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  simple_super_operations ; 

__attribute__((used)) static int pseudo_fs_fill_super(struct super_block *s, struct fs_context *fc)
{
	struct pseudo_fs_context *ctx = fc->fs_private;
	struct inode *root;

	s->s_maxbytes = MAX_LFS_FILESIZE;
	s->s_blocksize = PAGE_SIZE;
	s->s_blocksize_bits = PAGE_SHIFT;
	s->s_magic = ctx->magic;
	s->s_op = ctx->ops ?: &simple_super_operations;
	s->s_xattr = ctx->xattr;
	s->s_time_gran = 1;
	root = new_inode(s);
	if (!root)
		return -ENOMEM;

	/*
	 * since this is the first inode, make it number 1. New inodes created
	 * after this must take care not to collide with it (by passing
	 * max_reserved of 1 to iunique).
	 */
	root->i_ino = 1;
	root->i_mode = S_IFDIR | S_IRUSR | S_IWUSR;
	root->i_atime = root->i_mtime = root->i_ctime = current_time(root);
	s->s_root = d_make_root(root);
	if (!s->s_root)
		return -ENOMEM;
	s->s_d_op = ctx->dops;
	return 0;
}
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
struct super_block {int s_iflags; int /*<<< orphan*/  s_root; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; struct ipc_namespace* s_fs_info; } ;
struct ipc_namespace {int dummy; } ;
struct inode {int dummy; } ;
struct fs_context {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  MQUEUE_MAGIC ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct inode*) ; 
 int SB_I_NODEV ; 
 int SB_I_NOEXEC ; 
 int S_IFDIR ; 
 int S_IRWXUGO ; 
 int S_ISVTX ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 struct inode* mqueue_get_inode (struct super_block*,struct ipc_namespace*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mqueue_super_ops ; 

__attribute__((used)) static int mqueue_fill_super(struct super_block *sb, struct fs_context *fc)
{
	struct inode *inode;
	struct ipc_namespace *ns = sb->s_fs_info;

	sb->s_iflags |= SB_I_NOEXEC | SB_I_NODEV;
	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = MQUEUE_MAGIC;
	sb->s_op = &mqueue_super_ops;

	inode = mqueue_get_inode(sb, ns, S_IFDIR | S_ISVTX | S_IRWXUGO, NULL);
	if (IS_ERR(inode))
		return PTR_ERR(inode);

	sb->s_root = d_make_root(inode);
	if (!sb->s_root)
		return -ENOMEM;
	return 0;
}
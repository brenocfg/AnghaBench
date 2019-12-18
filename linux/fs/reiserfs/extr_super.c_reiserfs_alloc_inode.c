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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct reiserfs_inode_info {struct inode vfs_inode; int /*<<< orphan*/  i_dquot; int /*<<< orphan*/  tailpack; int /*<<< orphan*/  openers; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct reiserfs_inode_info* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reiserfs_inode_cachep ; 

__attribute__((used)) static struct inode *reiserfs_alloc_inode(struct super_block *sb)
{
	struct reiserfs_inode_info *ei;
	ei = kmem_cache_alloc(reiserfs_inode_cachep, GFP_KERNEL);
	if (!ei)
		return NULL;
	atomic_set(&ei->openers, 0);
	mutex_init(&ei->tailpack);
#ifdef CONFIG_QUOTA
	memset(&ei->i_dquot, 0, sizeof(ei->i_dquot));
#endif

	return &ei->vfs_inode;
}
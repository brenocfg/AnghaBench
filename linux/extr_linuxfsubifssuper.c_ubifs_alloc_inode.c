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
struct inode {int dummy; } ;
struct ubifs_inode {struct inode vfs_inode; int /*<<< orphan*/  ui_lock; int /*<<< orphan*/  ui_mutex; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct ubifs_inode* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_inode_slab ; 

__attribute__((used)) static struct inode *ubifs_alloc_inode(struct super_block *sb)
{
	struct ubifs_inode *ui;

	ui = kmem_cache_alloc(ubifs_inode_slab, GFP_NOFS);
	if (!ui)
		return NULL;

	memset((void *)ui + sizeof(struct inode), 0,
	       sizeof(struct ubifs_inode) - sizeof(struct inode));
	mutex_init(&ui->ui_mutex);
	spin_lock_init(&ui->ui_lock);
	return &ui->vfs_inode;
}
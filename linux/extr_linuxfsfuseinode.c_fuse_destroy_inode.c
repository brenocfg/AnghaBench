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
struct inode {int /*<<< orphan*/  i_rcu; } ;
struct fuse_inode {int /*<<< orphan*/  forget; int /*<<< orphan*/  mutex; int /*<<< orphan*/  queued_writes; int /*<<< orphan*/  write_files; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_i_callback ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_destroy_inode(struct inode *inode)
{
	struct fuse_inode *fi = get_fuse_inode(inode);
	BUG_ON(!list_empty(&fi->write_files));
	BUG_ON(!list_empty(&fi->queued_writes));
	mutex_destroy(&fi->mutex);
	kfree(fi->forget);
	call_rcu(&inode->i_rcu, fuse_i_callback);
}
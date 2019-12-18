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
struct fuse_inode {int /*<<< orphan*/  forget; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_inode_cachep ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fuse_inode*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_free_inode(struct inode *inode)
{
	struct fuse_inode *fi = get_fuse_inode(inode);

	mutex_destroy(&fi->mutex);
	kfree(fi->forget);
	kmem_cache_free(fuse_inode_cachep, fi);
}
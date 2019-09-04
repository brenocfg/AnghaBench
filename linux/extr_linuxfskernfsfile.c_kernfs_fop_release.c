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
struct kernfs_open_file {struct kernfs_open_file* prealloc_buf; } ;
struct kernfs_node {int flags; } ;
struct inode {struct kernfs_node* i_private; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int KERNFS_HAS_RELEASE ; 
 struct kernfs_open_file* kernfs_of (struct file*) ; 
 int /*<<< orphan*/  kernfs_open_file_mutex ; 
 int /*<<< orphan*/  kernfs_put_open_node (struct kernfs_node*,struct kernfs_open_file*) ; 
 int /*<<< orphan*/  kernfs_release_file (struct kernfs_node*,struct kernfs_open_file*) ; 
 int /*<<< orphan*/  kfree (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_release (struct inode*,struct file*) ; 

__attribute__((used)) static int kernfs_fop_release(struct inode *inode, struct file *filp)
{
	struct kernfs_node *kn = inode->i_private;
	struct kernfs_open_file *of = kernfs_of(filp);

	if (kn->flags & KERNFS_HAS_RELEASE) {
		mutex_lock(&kernfs_open_file_mutex);
		kernfs_release_file(kn, of);
		mutex_unlock(&kernfs_open_file_mutex);
	}

	kernfs_put_open_node(kn, of);
	seq_release(inode, filp);
	kfree(of->prealloc_buf);
	kfree(of);

	return 0;
}
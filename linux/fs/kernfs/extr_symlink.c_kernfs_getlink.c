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
struct TYPE_2__ {struct kernfs_node* target_kn; } ;
struct kernfs_node {TYPE_1__ symlink; struct kernfs_node* parent; } ;
struct inode {struct kernfs_node* i_private; } ;

/* Variables and functions */
 int kernfs_get_target_path (struct kernfs_node*,struct kernfs_node*,char*) ; 
 int /*<<< orphan*/  kernfs_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kernfs_getlink(struct inode *inode, char *path)
{
	struct kernfs_node *kn = inode->i_private;
	struct kernfs_node *parent = kn->parent;
	struct kernfs_node *target = kn->symlink.target_kn;
	int error;

	mutex_lock(&kernfs_mutex);
	error = kernfs_get_target_path(parent, target, path);
	mutex_unlock(&kernfs_mutex);

	return error;
}
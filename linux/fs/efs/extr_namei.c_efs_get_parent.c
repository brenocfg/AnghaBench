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
struct dentry {int /*<<< orphan*/  d_sb; } ;
typedef  scalar_t__ efs_ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 scalar_t__ efs_find_entry (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  efs_iget (int /*<<< orphan*/ ,scalar_t__) ; 

struct dentry *efs_get_parent(struct dentry *child)
{
	struct dentry *parent = ERR_PTR(-ENOENT);
	efs_ino_t ino;

	ino = efs_find_entry(d_inode(child), "..", 2);
	if (ino)
		parent = d_obtain_alias(efs_iget(child->d_sb, ino));

	return parent;
}
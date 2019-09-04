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
struct qstr {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct qstr QSTR_INIT (char*,int) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_iget (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long ext2_inode_by_name (int /*<<< orphan*/ ,struct qstr*) ; 

struct dentry *ext2_get_parent(struct dentry *child)
{
	struct qstr dotdot = QSTR_INIT("..", 2);
	unsigned long ino = ext2_inode_by_name(d_inode(child), &dotdot);
	if (!ino)
		return ERR_PTR(-ENOENT);
	return d_obtain_alias(ext2_iget(child->d_sb, ino));
}
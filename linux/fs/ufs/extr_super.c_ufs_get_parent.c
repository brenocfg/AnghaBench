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
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct qstr QSTR_INIT (char*,int) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufs_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufs_inode_by_name (int /*<<< orphan*/ ,struct qstr*) ; 

__attribute__((used)) static struct dentry *ufs_get_parent(struct dentry *child)
{
	struct qstr dot_dot = QSTR_INIT("..", 2);
	ino_t ino;

	ino = ufs_inode_by_name(d_inode(child), &dot_dot);
	if (!ino)
		return ERR_PTR(-ENOENT);
	return d_obtain_alias(ufs_iget(child->d_sb, ino));
}
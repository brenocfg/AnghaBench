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
struct page {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_CAST (struct page*) ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct page*) ; 
 struct qstr QSTR_INIT (char*,int) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* d_obtain_alias (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_iget (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long f2fs_inode_by_name (int /*<<< orphan*/ ,struct qstr*,struct page**) ; 

struct dentry *f2fs_get_parent(struct dentry *child)
{
	struct qstr dotdot = QSTR_INIT("..", 2);
	struct page *page;
	unsigned long ino = f2fs_inode_by_name(d_inode(child), &dotdot, &page);
	if (!ino) {
		if (IS_ERR(page))
			return ERR_CAST(page);
		return ERR_PTR(-ENOENT);
	}
	return d_obtain_alias(f2fs_iget(child->d_sb, ino));
}
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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; } ;
struct dentry {int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int f2fs_do_add_link (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int f2fs_add_link(struct dentry *dentry, struct inode *inode)
{
	return f2fs_do_add_link(d_inode(dentry->d_parent), &dentry->d_name,
				inode, inode->i_ino, inode->i_mode);
}
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
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; } ;
struct f2fs_dentry_ptr {int dummy; } ;

/* Variables and functions */
 struct qstr QSTR_INIT (char*,int) ; 
 int /*<<< orphan*/  f2fs_update_dentry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct f2fs_dentry_ptr*,struct qstr*,int /*<<< orphan*/ ,int) ; 

void f2fs_do_make_empty_dir(struct inode *inode, struct inode *parent,
					struct f2fs_dentry_ptr *d)
{
	struct qstr dot = QSTR_INIT(".", 1);
	struct qstr dotdot = QSTR_INIT("..", 2);

	/* update dirent of "." */
	f2fs_update_dentry(inode->i_ino, inode->i_mode, d, &dot, 0, 0);

	/* update dirent of ".." */
	f2fs_update_dentry(parent->i_ino, parent->i_mode, d, &dotdot, 0, 1);
}
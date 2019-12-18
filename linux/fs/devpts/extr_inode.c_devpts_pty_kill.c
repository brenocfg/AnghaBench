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
struct dentry {int /*<<< orphan*/  d_parent; int /*<<< orphan*/  d_inode; int /*<<< orphan*/ * d_fsdata; TYPE_1__* d_sb; } ;
struct TYPE_2__ {scalar_t__ s_magic; } ;

/* Variables and functions */
 scalar_t__ DEVPTS_SUPER_MAGIC ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  drop_nlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsnotify_unlink (int /*<<< orphan*/ ,struct dentry*) ; 

void devpts_pty_kill(struct dentry *dentry)
{
	WARN_ON_ONCE(dentry->d_sb->s_magic != DEVPTS_SUPER_MAGIC);

	dentry->d_fsdata = NULL;
	drop_nlink(dentry->d_inode);
	fsnotify_unlink(d_inode(dentry->d_parent), dentry);
	d_drop(dentry);
	dput(dentry);	/* d_alloc_name() in devpts_pty_new() */
}
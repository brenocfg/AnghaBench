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
struct dentry {void* d_fsdata; struct dentry* d_parent; } ;
struct TYPE_2__ {unsigned long ip_dir_lock_gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 TYPE_1__* OCFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 

void ocfs2_dentry_attach_gen(struct dentry *dentry)
{
	unsigned long gen =
		OCFS2_I(d_inode(dentry->d_parent))->ip_dir_lock_gen;
	BUG_ON(d_inode(dentry));
	dentry->d_fsdata = (void *)gen;
}
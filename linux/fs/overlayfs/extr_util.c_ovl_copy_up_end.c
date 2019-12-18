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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  ovl_inode_unlock (int /*<<< orphan*/ ) ; 

void ovl_copy_up_end(struct dentry *dentry)
{
	ovl_inode_unlock(d_inode(dentry));
}
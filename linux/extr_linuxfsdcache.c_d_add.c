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
struct inode {int /*<<< orphan*/  i_lock; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __d_add (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  security_d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 

void d_add(struct dentry *entry, struct inode *inode)
{
	if (inode) {
		security_d_instantiate(entry, inode);
		spin_lock(&inode->i_lock);
	}
	__d_add(entry, inode);
}
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
struct dentry {int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_eq_iversion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfat_d_version (struct dentry*) ; 

__attribute__((used)) static int vfat_revalidate_shortname(struct dentry *dentry)
{
	int ret = 1;
	spin_lock(&dentry->d_lock);
	if (!inode_eq_iversion(d_inode(dentry->d_parent), vfat_d_version(dentry)))
		ret = 0;
	spin_unlock(&dentry->d_lock);
	return ret;
}
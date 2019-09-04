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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  nid_t ;

/* Variables and functions */
 struct dentry* d_find_any_alias (struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct inode* igrab (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  parent_ino (struct dentry*) ; 

__attribute__((used)) static int get_parent_ino(struct inode *inode, nid_t *pino)
{
	struct dentry *dentry;

	inode = igrab(inode);
	dentry = d_find_any_alias(inode);
	iput(inode);
	if (!dentry)
		return 0;

	*pino = parent_ino(dentry);
	dput(dentry);
	return 1;
}
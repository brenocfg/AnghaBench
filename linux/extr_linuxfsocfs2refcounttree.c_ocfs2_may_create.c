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

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 scalar_t__ IS_DEADDIR (struct inode*) ; 
 int MAY_EXEC ; 
 int MAY_WRITE ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int inode_permission (struct inode*,int) ; 

__attribute__((used)) static inline int ocfs2_may_create(struct inode *dir, struct dentry *child)
{
	if (d_really_is_positive(child))
		return -EEXIST;
	if (IS_DEADDIR(dir))
		return -ENOENT;
	return inode_permission(dir, MAY_WRITE | MAY_EXEC);
}
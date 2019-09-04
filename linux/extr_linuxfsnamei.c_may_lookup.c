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
struct nameidata {int flags; int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int ECHILD ; 
 int LOOKUP_RCU ; 
 int MAY_EXEC ; 
 int MAY_NOT_BLOCK ; 
 int inode_permission (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlazy_walk (struct nameidata*) ; 

__attribute__((used)) static inline int may_lookup(struct nameidata *nd)
{
	if (nd->flags & LOOKUP_RCU) {
		int err = inode_permission(nd->inode, MAY_EXEC|MAY_NOT_BLOCK);
		if (err != -ECHILD)
			return err;
		if (unlazy_walk(nd))
			return -ECHILD;
	}
	return inode_permission(nd->inode, MAY_EXEC);
}
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
struct iattr {int ia_valid; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_UID ; 
 int /*<<< orphan*/  LOCKDOWN_DEBUGFS ; 
 int security_locked_down (int /*<<< orphan*/ ) ; 
 int simple_setattr (struct dentry*,struct iattr*) ; 

__attribute__((used)) static int debugfs_setattr(struct dentry *dentry, struct iattr *ia)
{
	int ret = security_locked_down(LOCKDOWN_DEBUGFS);

	if (ret && (ia->ia_valid & (ATTR_MODE | ATTR_UID | ATTR_GID)))
		return ret;
	return simple_setattr(dentry, ia);
}
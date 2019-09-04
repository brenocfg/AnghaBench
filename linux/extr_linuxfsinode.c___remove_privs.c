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
 int ATTR_FORCE ; 
 int notify_change (struct dentry*,struct iattr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __remove_privs(struct dentry *dentry, int kill)
{
	struct iattr newattrs;

	newattrs.ia_valid = ATTR_FORCE | kill;
	/*
	 * Note we call this on write, so notify_change will not
	 * encounter any conflicting delegations:
	 */
	return notify_change(dentry, &newattrs, NULL);
}
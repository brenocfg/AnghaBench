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
struct dentry {int d_flags; } ;

/* Variables and functions */
 int DCACHE_DISCONNECTED ; 
 scalar_t__ ovl_dentry_has_upper_alias (struct dentry*) ; 
 int /*<<< orphan*/  ovl_dentry_needs_data_copy_up_locked (struct dentry*,int) ; 
 scalar_t__ ovl_dentry_upper (struct dentry*) ; 

__attribute__((used)) static bool ovl_already_copied_up_locked(struct dentry *dentry, int flags)
{
	bool disconnected = dentry->d_flags & DCACHE_DISCONNECTED;

	if (ovl_dentry_upper(dentry) &&
	    (ovl_dentry_has_upper_alias(dentry) || disconnected) &&
	    !ovl_dentry_needs_data_copy_up_locked(dentry, flags))
		return true;

	return false;
}
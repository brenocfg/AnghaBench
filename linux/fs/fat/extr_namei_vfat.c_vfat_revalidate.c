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
 int ECHILD ; 
 unsigned int LOOKUP_RCU ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int vfat_revalidate_shortname (struct dentry*) ; 

__attribute__((used)) static int vfat_revalidate(struct dentry *dentry, unsigned int flags)
{
	if (flags & LOOKUP_RCU)
		return -ECHILD;

	/* This is not negative dentry. Always valid. */
	if (d_really_is_positive(dentry))
		return 1;
	return vfat_revalidate_shortname(dentry);
}
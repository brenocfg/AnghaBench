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

/* Variables and functions */
 scalar_t__ IS_PRIVATE (struct inode*) ; 
 int generic_permission (struct inode*,int) ; 

int reiserfs_permission(struct inode *inode, int mask)
{
	/*
	 * We don't do permission checks on the internal objects.
	 * Permissions are determined by the "owning" object.
	 */
	if (IS_PRIVATE(inode))
		return 0;

	return generic_permission(inode, mask);
}
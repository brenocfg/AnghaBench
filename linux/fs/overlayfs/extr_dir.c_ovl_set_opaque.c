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
 int /*<<< orphan*/  EIO ; 
 int ovl_set_opaque_xerr (struct dentry*,struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_set_opaque(struct dentry *dentry, struct dentry *upperdentry)
{
	/*
	 * Fail with -EIO when trying to create opaque dir and upper doesn't
	 * support xattrs. ovl_rename() calls ovl_set_opaque_xerr(-EXDEV) to
	 * return a specific error for noxattr case.
	 */
	return ovl_set_opaque_xerr(dentry, upperdentry, -EIO);
}
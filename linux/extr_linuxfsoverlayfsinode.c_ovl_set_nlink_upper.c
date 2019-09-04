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
 int /*<<< orphan*/  ovl_dentry_upper (struct dentry*) ; 
 int ovl_set_nlink_common (struct dentry*,int /*<<< orphan*/ ,char*) ; 

int ovl_set_nlink_upper(struct dentry *dentry)
{
	return ovl_set_nlink_common(dentry, ovl_dentry_upper(dentry), "U%+i");
}
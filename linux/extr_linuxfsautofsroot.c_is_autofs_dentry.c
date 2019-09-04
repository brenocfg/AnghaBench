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
struct dentry {int /*<<< orphan*/ * d_fsdata; int /*<<< orphan*/ * d_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  autofs_dentry_operations ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 

int is_autofs_dentry(struct dentry *dentry)
{
	return dentry && d_really_is_positive(dentry) &&
		dentry->d_op == &autofs_dentry_operations &&
		dentry->d_fsdata != NULL;
}
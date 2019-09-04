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
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  ovl_has_upperdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_open_flags_need_copy_up (int) ; 

bool ovl_dentry_needs_data_copy_up(struct dentry *dentry, int flags)
{
	if (!ovl_open_flags_need_copy_up(flags))
		return false;

	return !ovl_has_upperdata(d_inode(dentry));
}
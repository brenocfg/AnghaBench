#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 TYPE_1__* d_inode (struct dentry*) ; 
 scalar_t__ ovl_already_copied_up (struct dentry*,int) ; 
 int /*<<< orphan*/  ovl_open_flags_need_copy_up (int) ; 
 scalar_t__ special_file (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ovl_open_need_copy_up(struct dentry *dentry, int flags)
{
	/* Copy up of disconnected dentry does not set upper alias */
	if (ovl_already_copied_up(dentry, flags))
		return false;

	if (special_file(d_inode(dentry)->i_mode))
		return false;

	if (!ovl_open_flags_need_copy_up(flags))
		return false;

	return true;
}
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
struct ovl_entry {int numlower; } ;
struct dentry {struct ovl_entry* d_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_is_reg (struct dentry*) ; 
 scalar_t__ ovl_dentry_upper (struct dentry*) ; 
 int /*<<< orphan*/  ovl_has_upperdata (int /*<<< orphan*/ ) ; 

bool ovl_is_metacopy_dentry(struct dentry *dentry)
{
	struct ovl_entry *oe = dentry->d_fsdata;

	if (!d_is_reg(dentry))
		return false;

	if (ovl_dentry_upper(dentry)) {
		if (!ovl_has_upperdata(d_inode(dentry)))
			return true;
		return false;
	}

	return (oe->numlower > 1);
}
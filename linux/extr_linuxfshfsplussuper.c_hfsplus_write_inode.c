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
struct writeback_control {int dummy; } ;
struct inode {scalar_t__ i_ino; } ;

/* Variables and functions */
 scalar_t__ HFSPLUS_FIRSTUSER_CNID ; 
 scalar_t__ HFSPLUS_ROOT_CNID ; 
 int /*<<< orphan*/  INODE ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int hfsplus_cat_write_inode (struct inode*) ; 
 int hfsplus_ext_write_extent (struct inode*) ; 
 int hfsplus_system_write_inode (struct inode*) ; 

__attribute__((used)) static int hfsplus_write_inode(struct inode *inode,
		struct writeback_control *wbc)
{
	int err;

	hfs_dbg(INODE, "hfsplus_write_inode: %lu\n", inode->i_ino);

	err = hfsplus_ext_write_extent(inode);
	if (err)
		return err;

	if (inode->i_ino >= HFSPLUS_FIRSTUSER_CNID ||
	    inode->i_ino == HFSPLUS_ROOT_CNID)
		return hfsplus_cat_write_inode(inode);
	else
		return hfsplus_system_write_inode(inode);
}
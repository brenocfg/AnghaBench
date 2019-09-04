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
struct inode {int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_blkbits; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_nlink (struct inode*,int /*<<< orphan*/ ) ; 

void fsstack_copy_attr_all(struct inode *dest, const struct inode *src)
{
	dest->i_mode = src->i_mode;
	dest->i_uid = src->i_uid;
	dest->i_gid = src->i_gid;
	dest->i_rdev = src->i_rdev;
	dest->i_atime = src->i_atime;
	dest->i_mtime = src->i_mtime;
	dest->i_ctime = src->i_ctime;
	dest->i_blkbits = src->i_blkbits;
	dest->i_flags = src->i_flags;
	set_nlink(dest, src->i_nlink);
}
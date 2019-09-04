#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qstr {int dummy; } ;
struct TYPE_5__ {int i_mode; int /*<<< orphan*/  i_uid; } ;
struct gfs2_inode {TYPE_1__ i_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FOWNER ; 
 int EPERM ; 
 scalar_t__ IS_APPEND (TYPE_1__*) ; 
 scalar_t__ IS_IMMUTABLE (TYPE_1__*) ; 
 int MAY_EXEC ; 
 int MAY_WRITE ; 
 int S_ISVTX ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int gfs2_dir_check (TYPE_1__*,struct qstr const*,struct gfs2_inode const*) ; 
 int gfs2_permission (TYPE_1__*,int) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gfs2_unlink_ok(struct gfs2_inode *dip, const struct qstr *name,
			  const struct gfs2_inode *ip)
{
	int error;

	if (IS_IMMUTABLE(&ip->i_inode) || IS_APPEND(&ip->i_inode))
		return -EPERM;

	if ((dip->i_inode.i_mode & S_ISVTX) &&
	    !uid_eq(dip->i_inode.i_uid, current_fsuid()) &&
	    !uid_eq(ip->i_inode.i_uid, current_fsuid()) && !capable(CAP_FOWNER))
		return -EPERM;

	if (IS_APPEND(&dip->i_inode))
		return -EPERM;

	error = gfs2_permission(&dip->i_inode, MAY_WRITE | MAY_EXEC);
	if (error)
		return error;

	return gfs2_dir_check(&dip->i_inode, name, ip);
}
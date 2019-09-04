#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct TYPE_6__ {int i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct gfs2_inode {TYPE_3__ i_inode; } ;
struct TYPE_4__ {scalar_t__ ar_suiddir; } ;
struct TYPE_5__ {TYPE_1__ sd_args; } ;

/* Variables and functions */
 TYPE_2__* GFS2_SB (TYPE_3__*) ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_ISGID ; 
 int S_ISUID ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void munge_mode_uid_gid(const struct gfs2_inode *dip,
			       struct inode *inode)
{
	if (GFS2_SB(&dip->i_inode)->sd_args.ar_suiddir &&
	    (dip->i_inode.i_mode & S_ISUID) &&
	    !uid_eq(dip->i_inode.i_uid, GLOBAL_ROOT_UID)) {
		if (S_ISDIR(inode->i_mode))
			inode->i_mode |= S_ISUID;
		else if (!uid_eq(dip->i_inode.i_uid, current_fsuid()))
			inode->i_mode &= ~07111;
		inode->i_uid = dip->i_inode.i_uid;
	} else
		inode->i_uid = current_fsuid();

	if (dip->i_inode.i_mode & S_ISGID) {
		if (S_ISDIR(inode->i_mode))
			inode->i_mode |= S_ISGID;
		inode->i_gid = dip->i_inode.i_gid;
	} else
		inode->i_gid = current_fsgid();
}
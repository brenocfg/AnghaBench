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
struct inode {int i_flags; int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_nlink; } ;
struct hfsplus_perm {void* dev; void* group; void* owner; int /*<<< orphan*/  mode; int /*<<< orphan*/  userflags; int /*<<< orphan*/  rootflags; } ;
struct TYPE_2__ {int /*<<< orphan*/  userflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFSPLUS_FLG_APPEND ; 
 int /*<<< orphan*/  HFSPLUS_FLG_IMMUTABLE ; 
 TYPE_1__* HFSPLUS_I (struct inode*) ; 
 int S_APPEND ; 
 int S_IMMUTABLE ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_gid_read (struct inode*) ; 
 int /*<<< orphan*/  i_uid_read (struct inode*) ; 

void hfsplus_cat_set_perms(struct inode *inode, struct hfsplus_perm *perms)
{
	if (inode->i_flags & S_IMMUTABLE)
		perms->rootflags |= HFSPLUS_FLG_IMMUTABLE;
	else
		perms->rootflags &= ~HFSPLUS_FLG_IMMUTABLE;
	if (inode->i_flags & S_APPEND)
		perms->rootflags |= HFSPLUS_FLG_APPEND;
	else
		perms->rootflags &= ~HFSPLUS_FLG_APPEND;

	perms->userflags = HFSPLUS_I(inode)->userflags;
	perms->mode = cpu_to_be16(inode->i_mode);
	perms->owner = cpu_to_be32(i_uid_read(inode));
	perms->group = cpu_to_be32(i_gid_read(inode));

	if (S_ISREG(inode->i_mode))
		perms->dev = cpu_to_be32(inode->i_nlink);
	else if (S_ISBLK(inode->i_mode) || S_ISCHR(inode->i_mode))
		perms->dev = cpu_to_be32(inode->i_rdev);
	else
		perms->dev = 0;
}
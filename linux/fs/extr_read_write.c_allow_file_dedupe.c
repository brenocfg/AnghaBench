#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {int f_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 TYPE_1__* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_permission (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool allow_file_dedupe(struct file *file)
{
	if (capable(CAP_SYS_ADMIN))
		return true;
	if (file->f_mode & FMODE_WRITE)
		return true;
	if (uid_eq(current_fsuid(), file_inode(file)->i_uid))
		return true;
	if (!inode_permission(file_inode(file), MAY_WRITE))
		return true;
	return false;
}
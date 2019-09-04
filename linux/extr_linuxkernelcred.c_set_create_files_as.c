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
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct cred {int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int security_kernel_create_files_as (struct cred*,struct inode*) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

int set_create_files_as(struct cred *new, struct inode *inode)
{
	if (!uid_valid(inode->i_uid) || !gid_valid(inode->i_gid))
		return -EINVAL;
	new->fsuid = inode->i_uid;
	new->fsgid = inode->i_gid;
	return security_kernel_create_files_as(new, inode);
}
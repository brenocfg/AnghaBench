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
typedef  int umode_t ;
struct udf_inode_info {int /*<<< orphan*/  i_extraPerms; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_DELETE_PERMS ; 
 int /*<<< orphan*/  FE_PERM_G_DELETE ; 
 int /*<<< orphan*/  FE_PERM_O_DELETE ; 
 int /*<<< orphan*/  FE_PERM_U_DELETE ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 

void udf_update_extra_perms(struct inode *inode, umode_t mode)
{
	struct udf_inode_info *iinfo = UDF_I(inode);

	/*
	 * UDF 2.01 sec. 3.3.3.3 Note 2:
	 * In Unix, delete permission tracks write
	 */
	iinfo->i_extraPerms &= ~FE_DELETE_PERMS;
	if (mode & 0200)
		iinfo->i_extraPerms |= FE_PERM_U_DELETE;
	if (mode & 0020)
		iinfo->i_extraPerms |= FE_PERM_G_DELETE;
	if (mode & 0002)
		iinfo->i_extraPerms |= FE_PERM_O_DELETE;
}
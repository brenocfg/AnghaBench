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
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct iattr {int ia_valid; scalar_t__ ia_size; int /*<<< orphan*/  ia_mode; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_gid; int /*<<< orphan*/  s_uid; } ;

/* Variables and functions */
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_SIZE ; 
 int ATTR_UID ; 
 int EPERM ; 
 int /*<<< orphan*/  UDF_FLAG_GID_SET ; 
 int /*<<< orphan*/  UDF_FLAG_UID_SET ; 
 scalar_t__ UDF_QUERY_FLAG (struct super_block*,int /*<<< orphan*/ ) ; 
 TYPE_1__* UDF_SB (struct super_block*) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  setattr_copy (struct inode*,struct iattr*) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 
 int udf_setsize (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  udf_update_extra_perms (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udf_setattr(struct dentry *dentry, struct iattr *attr)
{
	struct inode *inode = d_inode(dentry);
	struct super_block *sb = inode->i_sb;
	int error;

	error = setattr_prepare(dentry, attr);
	if (error)
		return error;

	if ((attr->ia_valid & ATTR_UID) &&
	    UDF_QUERY_FLAG(sb, UDF_FLAG_UID_SET) &&
	    !uid_eq(attr->ia_uid, UDF_SB(sb)->s_uid))
		return -EPERM;
	if ((attr->ia_valid & ATTR_GID) &&
	    UDF_QUERY_FLAG(sb, UDF_FLAG_GID_SET) &&
	    !gid_eq(attr->ia_gid, UDF_SB(sb)->s_gid))
		return -EPERM;

	if ((attr->ia_valid & ATTR_SIZE) &&
	    attr->ia_size != i_size_read(inode)) {
		error = udf_setsize(inode, attr->ia_size);
		if (error)
			return error;
	}

	if (attr->ia_valid & ATTR_MODE)
		udf_update_extra_perms(inode, attr->ia_mode);

	setattr_copy(inode, attr);
	mark_inode_dirty(inode);
	return 0;
}
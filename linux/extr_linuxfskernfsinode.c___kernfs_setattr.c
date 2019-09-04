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
typedef  int /*<<< orphan*/  umode_t ;
struct kernfs_node {int /*<<< orphan*/  mode; } ;
struct iattr {unsigned int ia_valid; int /*<<< orphan*/  ia_mode; int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
struct kernfs_iattrs {struct iattr ia_iattr; } ;

/* Variables and functions */
 unsigned int ATTR_ATIME ; 
 unsigned int ATTR_CTIME ; 
 unsigned int ATTR_GID ; 
 unsigned int ATTR_MODE ; 
 unsigned int ATTR_MTIME ; 
 unsigned int ATTR_UID ; 
 int ENOMEM ; 
 struct kernfs_iattrs* kernfs_iattrs (struct kernfs_node*) ; 

int __kernfs_setattr(struct kernfs_node *kn, const struct iattr *iattr)
{
	struct kernfs_iattrs *attrs;
	struct iattr *iattrs;
	unsigned int ia_valid = iattr->ia_valid;

	attrs = kernfs_iattrs(kn);
	if (!attrs)
		return -ENOMEM;

	iattrs = &attrs->ia_iattr;

	if (ia_valid & ATTR_UID)
		iattrs->ia_uid = iattr->ia_uid;
	if (ia_valid & ATTR_GID)
		iattrs->ia_gid = iattr->ia_gid;
	if (ia_valid & ATTR_ATIME)
		iattrs->ia_atime = iattr->ia_atime;
	if (ia_valid & ATTR_MTIME)
		iattrs->ia_mtime = iattr->ia_mtime;
	if (ia_valid & ATTR_CTIME)
		iattrs->ia_ctime = iattr->ia_ctime;
	if (ia_valid & ATTR_MODE) {
		umode_t mode = iattr->ia_mode;
		iattrs->ia_mode = kn->mode = mode;
	}
	return 0;
}
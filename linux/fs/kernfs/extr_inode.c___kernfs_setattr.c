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
struct kernfs_node {int /*<<< orphan*/  mode; } ;
struct kernfs_iattrs {int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
struct iattr {unsigned int ia_valid; int /*<<< orphan*/  ia_mode; int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_atime; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;

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
	unsigned int ia_valid = iattr->ia_valid;

	attrs = kernfs_iattrs(kn);
	if (!attrs)
		return -ENOMEM;

	if (ia_valid & ATTR_UID)
		attrs->ia_uid = iattr->ia_uid;
	if (ia_valid & ATTR_GID)
		attrs->ia_gid = iattr->ia_gid;
	if (ia_valid & ATTR_ATIME)
		attrs->ia_atime = iattr->ia_atime;
	if (ia_valid & ATTR_MTIME)
		attrs->ia_mtime = iattr->ia_mtime;
	if (ia_valid & ATTR_CTIME)
		attrs->ia_ctime = iattr->ia_ctime;
	if (ia_valid & ATTR_MODE)
		kn->mode = iattr->ia_mode;
	return 0;
}
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
typedef  int u32 ;
struct yfs_xdr_YFSStoreStatus {void* group; void* owner; void* mtime_client; void* mode; void* mask; } ;
struct iattr {int ia_valid; int ia_mode; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; int /*<<< orphan*/  ia_mtime; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int AFS_SET_GROUP ; 
 int AFS_SET_MODE ; 
 int AFS_SET_MTIME ; 
 int AFS_SET_OWNER ; 
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_MTIME ; 
 int ATTR_UID ; 
 int S_IALLUGO ; 
 int /*<<< orphan*/  from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  linux_to_yfs_time (int /*<<< orphan*/ *) ; 
 void* u64_to_xdr (int /*<<< orphan*/ ) ; 
 int xdr_size (struct yfs_xdr_YFSStoreStatus*) ; 

__attribute__((used)) static __be32 *xdr_encode_YFS_StoreStatus(__be32 *bp, struct iattr *attr)
{
	struct yfs_xdr_YFSStoreStatus *x = (void *)bp;
	s64 mtime = 0, owner = 0, group = 0;
	u32 mask = 0, mode = 0;

	mask = 0;
	if (attr->ia_valid & ATTR_MTIME) {
		mask |= AFS_SET_MTIME;
		mtime = linux_to_yfs_time(&attr->ia_mtime);
	}

	if (attr->ia_valid & ATTR_UID) {
		mask |= AFS_SET_OWNER;
		owner = from_kuid(&init_user_ns, attr->ia_uid);
	}

	if (attr->ia_valid & ATTR_GID) {
		mask |= AFS_SET_GROUP;
		group = from_kgid(&init_user_ns, attr->ia_gid);
	}

	if (attr->ia_valid & ATTR_MODE) {
		mask |= AFS_SET_MODE;
		mode = attr->ia_mode & S_IALLUGO;
	}

	x->mask		= htonl(mask);
	x->mode		= htonl(mode);
	x->mtime_client	= u64_to_xdr(mtime);
	x->owner	= u64_to_xdr(owner);
	x->group	= u64_to_xdr(group);
	return bp + xdr_size(x);
}
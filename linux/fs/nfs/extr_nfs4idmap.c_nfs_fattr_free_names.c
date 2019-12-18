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
struct nfs_fattr {int valid; } ;

/* Variables and functions */
 int NFS_ATTR_FATTR_GROUP_NAME ; 
 int NFS_ATTR_FATTR_OWNER_NAME ; 
 int /*<<< orphan*/  nfs_fattr_free_group_name (struct nfs_fattr*) ; 
 int /*<<< orphan*/  nfs_fattr_free_owner_name (struct nfs_fattr*) ; 

void nfs_fattr_free_names(struct nfs_fattr *fattr)
{
	if (fattr->valid & NFS_ATTR_FATTR_OWNER_NAME)
		nfs_fattr_free_owner_name(fattr);
	if (fattr->valid & NFS_ATTR_FATTR_GROUP_NAME)
		nfs_fattr_free_group_name(fattr);
}
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
 int NFS_ATTR_FATTR_MOUNTED_ON_FILEID ; 
 int NFS_ATTR_FATTR_MOUNTPOINT ; 
 int NFS_ATTR_FATTR_V4_REFERRAL ; 

__attribute__((used)) static inline int nfs_attr_use_mounted_on_fileid(struct nfs_fattr *fattr)
{
	if (((fattr->valid & NFS_ATTR_FATTR_MOUNTED_ON_FILEID) == 0) ||
	    (((fattr->valid & NFS_ATTR_FATTR_MOUNTPOINT) == 0) &&
	     ((fattr->valid & NFS_ATTR_FATTR_V4_REFERRAL) == 0)))
		return 0;
	return 1;
}
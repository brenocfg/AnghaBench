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
struct nfs_inode {scalar_t__ fileid; } ;
struct nfs_fattr {int valid; scalar_t__ fileid; scalar_t__ mounted_on_fileid; } ;

/* Variables and functions */
 int NFS_ATTR_FATTR_FILEID ; 
 int NFS_ATTR_FATTR_MOUNTED_ON_FILEID ; 

__attribute__((used)) static inline bool nfs_fileid_valid(struct nfs_inode *nfsi,
				    struct nfs_fattr *fattr)
{
	bool ret1 = true, ret2 = true;

	if (fattr->valid & NFS_ATTR_FATTR_FILEID)
		ret1 = (nfsi->fileid == fattr->fileid);
	if (fattr->valid & NFS_ATTR_FATTR_MOUNTED_ON_FILEID)
		ret2 = (nfsi->fileid == fattr->mounted_on_fileid);
	return ret1 || ret2;
}
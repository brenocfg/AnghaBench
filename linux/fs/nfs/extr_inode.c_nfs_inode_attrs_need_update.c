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
struct nfs_inode {scalar_t__ attr_gencount; } ;
struct nfs_fattr {scalar_t__ gencount; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (struct inode const*) ; 
 scalar_t__ nfs_read_attr_generation_counter () ; 

__attribute__((used)) static int nfs_inode_attrs_need_update(const struct inode *inode, const struct nfs_fattr *fattr)
{
	const struct nfs_inode *nfsi = NFS_I(inode);

	return ((long)fattr->gencount - (long)nfsi->attr_gencount) > 0 ||
		((long)nfsi->attr_gencount - (long)nfs_read_attr_generation_counter() > 0);
}
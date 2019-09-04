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
struct nfs_direct_req {int dummy; } ;
struct nfs_commit_info {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_init_cinfo_from_dreq (struct nfs_commit_info*,struct nfs_direct_req*) ; 
 int /*<<< orphan*/  nfs_init_cinfo_from_inode (struct nfs_commit_info*,struct inode*) ; 

void nfs_init_cinfo(struct nfs_commit_info *cinfo,
		    struct inode *inode,
		    struct nfs_direct_req *dreq)
{
	if (dreq)
		nfs_init_cinfo_from_dreq(cinfo, dreq);
	else
		nfs_init_cinfo_from_inode(cinfo, inode);
}
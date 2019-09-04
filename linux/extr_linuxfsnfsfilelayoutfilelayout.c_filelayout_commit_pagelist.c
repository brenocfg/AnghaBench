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
struct nfs_commit_info {int dummy; } ;
struct list_head {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  filelayout_initiate_commit ; 
 int pnfs_generic_commit_pagelist (struct inode*,struct list_head*,int,struct nfs_commit_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
filelayout_commit_pagelist(struct inode *inode, struct list_head *mds_pages,
			   int how, struct nfs_commit_info *cinfo)
{
	return pnfs_generic_commit_pagelist(inode, mds_pages, how, cinfo,
					    filelayout_initiate_commit);
}
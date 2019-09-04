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
struct nfs_direct_req {int /*<<< orphan*/  ds_cinfo; int /*<<< orphan*/  mds_cinfo; int /*<<< orphan*/  inode; } ;
struct nfs_commit_info {int /*<<< orphan*/ * completion_ops; struct nfs_direct_req* dreq; int /*<<< orphan*/ * ds; int /*<<< orphan*/ * mds; int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_direct_commit_completion_ops ; 

void nfs_init_cinfo_from_dreq(struct nfs_commit_info *cinfo,
			      struct nfs_direct_req *dreq)
{
	cinfo->inode = dreq->inode;
	cinfo->mds = &dreq->mds_cinfo;
	cinfo->ds = &dreq->ds_cinfo;
	cinfo->dreq = dreq;
	cinfo->completion_ops = &nfs_direct_commit_completion_ops;
}
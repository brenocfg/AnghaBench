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
struct nfs_direct_req {int /*<<< orphan*/  inode; } ;
struct nfs_commit_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mds_list ; 
 int /*<<< orphan*/  nfs_direct_write_reschedule (struct nfs_direct_req*) ; 
 int nfs_generic_commit_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nfs_commit_info*) ; 
 int /*<<< orphan*/  nfs_init_cinfo_from_dreq (struct nfs_commit_info*,struct nfs_direct_req*) ; 
 int /*<<< orphan*/  nfs_scan_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfs_commit_info*) ; 

__attribute__((used)) static void nfs_direct_commit_schedule(struct nfs_direct_req *dreq)
{
	int res;
	struct nfs_commit_info cinfo;
	LIST_HEAD(mds_list);

	nfs_init_cinfo_from_dreq(&cinfo, dreq);
	nfs_scan_commit(dreq->inode, &mds_list, &cinfo);
	res = nfs_generic_commit_list(dreq->inode, &mds_list, 0, &cinfo);
	if (res < 0) /* res == -ENOMEM */
		nfs_direct_write_reschedule(dreq);
}
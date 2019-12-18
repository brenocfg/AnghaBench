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
struct nfs_page {int dummy; } ;
struct nfs_direct_req {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct nfs_commit_info {struct nfs_direct_req* dreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_ODIRECT_RESCHED_WRITES ; 
 int /*<<< orphan*/  nfs_mark_request_commit (struct nfs_page*,int /*<<< orphan*/ *,struct nfs_commit_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_direct_resched_write(struct nfs_commit_info *cinfo,
		struct nfs_page *req)
{
	struct nfs_direct_req *dreq = cinfo->dreq;

	spin_lock(&dreq->lock);
	dreq->flags = NFS_ODIRECT_RESCHED_WRITES;
	spin_unlock(&dreq->lock);
	nfs_mark_request_commit(req, NULL, cinfo, 0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
struct TYPE_3__ {int /*<<< orphan*/  committed; } ;
struct nfs_pgio_header {TYPE_2__ args; int /*<<< orphan*/  good_bytes; TYPE_1__ verf; struct nfs_direct_req* dreq; } ;
struct nfs_direct_req {scalar_t__ error; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_ODIRECT_RESCHED_WRITES ; 
 int /*<<< orphan*/  NFS_UNSTABLE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_direct_write_reschedule_io(struct nfs_pgio_header *hdr)
{
	struct nfs_direct_req *dreq = hdr->dreq;

	spin_lock(&dreq->lock);
	if (dreq->error == 0) {
		dreq->flags = NFS_ODIRECT_RESCHED_WRITES;
		/* fake unstable write to let common nfs resend pages */
		hdr->verf.committed = NFS_UNSTABLE;
		hdr->good_bytes = hdr->args.count;
	}
	spin_unlock(&dreq->lock);
}
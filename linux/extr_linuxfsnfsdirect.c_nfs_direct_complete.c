#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfs_direct_req {scalar_t__ count; int /*<<< orphan*/  completion; TYPE_1__* iocb; scalar_t__ error; struct inode* inode; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ki_complete ) (TYPE_1__*,long,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_dio_end (struct inode*) ; 
 int /*<<< orphan*/  nfs_direct_req_release (struct nfs_direct_req*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_direct_complete(struct nfs_direct_req *dreq)
{
	struct inode *inode = dreq->inode;

	inode_dio_end(inode);

	if (dreq->iocb) {
		long res = (long) dreq->error;
		if (dreq->count != 0) {
			res = (long) dreq->count;
			WARN_ON_ONCE(dreq->count < 0);
		}
		dreq->iocb->ki_complete(dreq->iocb, res, 0);
	}

	complete(&dreq->completion);

	nfs_direct_req_release(dreq);
}
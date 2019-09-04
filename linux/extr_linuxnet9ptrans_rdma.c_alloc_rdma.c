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
struct p9_trans_rdma {int /*<<< orphan*/  excess_rc; int /*<<< orphan*/  rq_depth; int /*<<< orphan*/  rq_sem; int /*<<< orphan*/  sq_depth; int /*<<< orphan*/  sq_sem; int /*<<< orphan*/  cm_done; int /*<<< orphan*/  req_lock; int /*<<< orphan*/  timeout; int /*<<< orphan*/  privport; int /*<<< orphan*/  port; } ;
struct p9_rdma_opts {int /*<<< orphan*/  timeout; int /*<<< orphan*/  rq_depth; int /*<<< orphan*/  sq_depth; int /*<<< orphan*/  privport; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct p9_trans_rdma* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct p9_trans_rdma *alloc_rdma(struct p9_rdma_opts *opts)
{
	struct p9_trans_rdma *rdma;

	rdma = kzalloc(sizeof(struct p9_trans_rdma), GFP_KERNEL);
	if (!rdma)
		return NULL;

	rdma->port = opts->port;
	rdma->privport = opts->privport;
	rdma->sq_depth = opts->sq_depth;
	rdma->rq_depth = opts->rq_depth;
	rdma->timeout = opts->timeout;
	spin_lock_init(&rdma->req_lock);
	init_completion(&rdma->cm_done);
	sema_init(&rdma->sq_sem, rdma->sq_depth);
	sema_init(&rdma->rq_sem, rdma->rq_depth);
	atomic_set(&rdma->excess_rc, 0);

	return rdma;
}
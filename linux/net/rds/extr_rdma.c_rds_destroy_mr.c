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
struct rds_sock {int /*<<< orphan*/  rs_rdma_lock; int /*<<< orphan*/  rs_rdma_keys; } ;
struct rds_mr {int /*<<< orphan*/  r_invalidate; TYPE_1__* r_trans; int /*<<< orphan*/ * r_trans_private; int /*<<< orphan*/  r_rb_node; int /*<<< orphan*/  r_state; int /*<<< orphan*/  r_refcount; int /*<<< orphan*/  r_key; struct rds_sock* r_sock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_mr ) (void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RDS_MR_DEAD ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdsdebug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rds_destroy_mr(struct rds_mr *mr)
{
	struct rds_sock *rs = mr->r_sock;
	void *trans_private = NULL;
	unsigned long flags;

	rdsdebug("RDS: destroy mr key is %x refcnt %u\n",
			mr->r_key, refcount_read(&mr->r_refcount));

	if (test_and_set_bit(RDS_MR_DEAD, &mr->r_state))
		return;

	spin_lock_irqsave(&rs->rs_rdma_lock, flags);
	if (!RB_EMPTY_NODE(&mr->r_rb_node))
		rb_erase(&mr->r_rb_node, &rs->rs_rdma_keys);
	trans_private = mr->r_trans_private;
	mr->r_trans_private = NULL;
	spin_unlock_irqrestore(&rs->rs_rdma_lock, flags);

	if (trans_private)
		mr->r_trans->free_mr(trans_private, mr->r_invalidate);
}
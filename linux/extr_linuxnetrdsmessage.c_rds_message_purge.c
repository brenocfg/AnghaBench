#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rds_sock {int dummy; } ;
struct TYPE_6__ {scalar_t__ op_rdma_mr; scalar_t__ op_active; } ;
struct TYPE_5__ {scalar_t__ op_rdma_mr; scalar_t__ op_active; } ;
struct TYPE_4__ {unsigned long op_nents; int /*<<< orphan*/ * op_sg; int /*<<< orphan*/ * op_mmp_znotifier; } ;
struct rds_message {TYPE_3__ atomic; TYPE_2__ rdma; TYPE_1__ data; int /*<<< orphan*/  m_rs_lock; struct rds_sock* m_rs; int /*<<< orphan*/  m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_MSG_PAGEVEC ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_atomic_free_op (TYPE_3__*) ; 
 int /*<<< orphan*/  rds_mr_put (scalar_t__) ; 
 int /*<<< orphan*/  rds_rdma_free_op (TYPE_2__*) ; 
 int /*<<< orphan*/  rds_rm_zerocopy_callback (struct rds_sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_rs_to_sk (struct rds_sock*) ; 
 int /*<<< orphan*/  rds_wake_sk_sleep (struct rds_sock*) ; 
 int /*<<< orphan*/  sg_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rds_message_purge(struct rds_message *rm)
{
	unsigned long i, flags;
	bool zcopy = false;

	if (unlikely(test_bit(RDS_MSG_PAGEVEC, &rm->m_flags)))
		return;

	spin_lock_irqsave(&rm->m_rs_lock, flags);
	if (rm->m_rs) {
		struct rds_sock *rs = rm->m_rs;

		if (rm->data.op_mmp_znotifier) {
			zcopy = true;
			rds_rm_zerocopy_callback(rs, rm->data.op_mmp_znotifier);
			rds_wake_sk_sleep(rs);
			rm->data.op_mmp_znotifier = NULL;
		}
		sock_put(rds_rs_to_sk(rs));
		rm->m_rs = NULL;
	}
	spin_unlock_irqrestore(&rm->m_rs_lock, flags);

	for (i = 0; i < rm->data.op_nents; i++) {
		/* XXX will have to put_page for page refs */
		if (!zcopy)
			__free_page(sg_page(&rm->data.op_sg[i]));
		else
			put_page(sg_page(&rm->data.op_sg[i]));
	}
	rm->data.op_nents = 0;

	if (rm->rdma.op_active)
		rds_rdma_free_op(&rm->rdma);
	if (rm->rdma.op_rdma_mr)
		rds_mr_put(rm->rdma.op_rdma_mr);

	if (rm->atomic.op_active)
		rds_atomic_free_op(&rm->atomic);
	if (rm->atomic.op_rdma_mr)
		rds_mr_put(rm->atomic.op_rdma_mr);
}
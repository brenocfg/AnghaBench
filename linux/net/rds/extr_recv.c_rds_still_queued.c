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
struct sock {int dummy; } ;
struct rds_sock {int /*<<< orphan*/  rs_recv_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  h_dport; int /*<<< orphan*/  h_len; } ;
struct rds_incoming {int /*<<< orphan*/  i_item; TYPE_2__ i_hdr; TYPE_1__* i_conn; } ;
struct TYPE_3__ {int /*<<< orphan*/  c_lcong; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_inc_put (struct rds_incoming*) ; 
 int /*<<< orphan*/  rds_recv_rcvbuf_delta (struct rds_sock*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sock* rds_rs_to_sk (struct rds_sock*) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_incoming*,struct rds_sock*,int,int) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rds_still_queued(struct rds_sock *rs, struct rds_incoming *inc,
			    int drop)
{
	struct sock *sk = rds_rs_to_sk(rs);
	int ret = 0;
	unsigned long flags;

	write_lock_irqsave(&rs->rs_recv_lock, flags);
	if (!list_empty(&inc->i_item)) {
		ret = 1;
		if (drop) {
			/* XXX make sure this i_conn is reliable */
			rds_recv_rcvbuf_delta(rs, sk, inc->i_conn->c_lcong,
					      -be32_to_cpu(inc->i_hdr.h_len),
					      inc->i_hdr.h_dport);
			list_del_init(&inc->i_item);
			rds_inc_put(inc);
		}
	}
	write_unlock_irqrestore(&rs->rs_recv_lock, flags);

	rdsdebug("inc %p rs %p still %d dropped %d\n", inc, rs, ret, drop);
	return ret;
}
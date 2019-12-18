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
struct rds_ib_connection {struct rds_connection* conn; int /*<<< orphan*/  i_send_wc; int /*<<< orphan*/  i_send_cq; int /*<<< orphan*/  i_cq_quiesce; } ;
struct rds_connection {int /*<<< orphan*/ * c_path; int /*<<< orphan*/  c_map_queued; int /*<<< orphan*/  c_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_CQ_NEXT_COMP ; 
 int /*<<< orphan*/  RDS_LL_SEND_FULL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_req_notify_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_scq (struct rds_ib_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rds_conn_up (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_ib_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_send_xmit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_ib_tasklet_call ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rds_ib_tasklet_fn_send(unsigned long data)
{
	struct rds_ib_connection *ic = (struct rds_ib_connection *)data;
	struct rds_connection *conn = ic->conn;

	rds_ib_stats_inc(s_ib_tasklet_call);

	/* if cq has been already reaped, ignore incoming cq event */
	if (atomic_read(&ic->i_cq_quiesce))
		return;

	poll_scq(ic, ic->i_send_cq, ic->i_send_wc);
	ib_req_notify_cq(ic->i_send_cq, IB_CQ_NEXT_COMP);
	poll_scq(ic, ic->i_send_cq, ic->i_send_wc);

	if (rds_conn_up(conn) &&
	    (!test_bit(RDS_LL_SEND_FULL, &conn->c_flags) ||
	    test_bit(0, &conn->c_map_queued)))
		rds_send_xmit(&ic->conn->c_path[0]);
}
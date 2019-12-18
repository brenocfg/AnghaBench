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
struct rds_ib_device {int dummy; } ;
struct rds_ib_connection {scalar_t__ i_ack_recv; int /*<<< orphan*/  i_recv_wc; int /*<<< orphan*/  i_recv_cq; int /*<<< orphan*/  i_cq_quiesce; struct rds_ib_device* rds_ibdev; struct rds_connection* conn; } ;
struct rds_ib_ack_state {scalar_t__ ack_recv; scalar_t__ ack_recv_valid; int /*<<< orphan*/  ack_required; int /*<<< orphan*/  ack_next; scalar_t__ ack_next_valid; } ;
struct rds_connection {int dummy; } ;
typedef  int /*<<< orphan*/  state ;

/* Variables and functions */
 int /*<<< orphan*/  IB_CQ_SOLICITED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_req_notify_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rds_ib_ack_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  poll_rcq (struct rds_ib_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rds_ib_ack_state*) ; 
 int /*<<< orphan*/  rds_conn_drop (struct rds_connection*) ; 
 scalar_t__ rds_conn_up (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_ib_attempt_ack (struct rds_ib_connection*) ; 
 int /*<<< orphan*/  rds_ib_set_ack (struct rds_ib_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_ib_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_send_drop_acked (struct rds_connection*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_ib_tasklet_call ; 

__attribute__((used)) static void rds_ib_tasklet_fn_recv(unsigned long data)
{
	struct rds_ib_connection *ic = (struct rds_ib_connection *)data;
	struct rds_connection *conn = ic->conn;
	struct rds_ib_device *rds_ibdev = ic->rds_ibdev;
	struct rds_ib_ack_state state;

	if (!rds_ibdev)
		rds_conn_drop(conn);

	rds_ib_stats_inc(s_ib_tasklet_call);

	/* if cq has been already reaped, ignore incoming cq event */
	if (atomic_read(&ic->i_cq_quiesce))
		return;

	memset(&state, 0, sizeof(state));
	poll_rcq(ic, ic->i_recv_cq, ic->i_recv_wc, &state);
	ib_req_notify_cq(ic->i_recv_cq, IB_CQ_SOLICITED);
	poll_rcq(ic, ic->i_recv_cq, ic->i_recv_wc, &state);

	if (state.ack_next_valid)
		rds_ib_set_ack(ic, state.ack_next, state.ack_required);
	if (state.ack_recv_valid && state.ack_recv > ic->i_ack_recv) {
		rds_send_drop_acked(conn, state.ack_recv, NULL);
		ic->i_ack_recv = state.ack_recv;
	}

	if (rds_conn_up(conn))
		rds_ib_attempt_ack(ic);
}
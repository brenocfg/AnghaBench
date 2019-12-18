#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct rds_message {scalar_t__ m_final_op; } ;
struct TYPE_7__ {int send_flags; } ;
struct rds_ib_send_work {scalar_t__ s_op; scalar_t__ s_queued; TYPE_2__ s_wr; } ;
struct TYPE_8__ {scalar_t__ w_nr; } ;
struct rds_ib_connection {TYPE_3__ i_send_ring; struct rds_ib_send_work* i_sends; scalar_t__ i_ack_queued; struct rds_connection* conn; } ;
struct rds_connection {int /*<<< orphan*/  c_tos; int /*<<< orphan*/  c_faddr; int /*<<< orphan*/  c_laddr; int /*<<< orphan*/  c_send_w; int /*<<< orphan*/  c_map_queued; int /*<<< orphan*/  c_flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  imm_data; } ;
struct ib_wc {scalar_t__ wr_id; int /*<<< orphan*/  status; TYPE_1__ ex; int /*<<< orphan*/  byte_len; } ;

/* Variables and functions */
 int HZ ; 
 int IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 scalar_t__ RDS_IB_ACK_WR_ID ; 
 int /*<<< orphan*/  RDS_LL_SEND_FULL ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_wc_status_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rds_conn_up (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_ib_ack_send_complete (struct rds_ib_connection*) ; 
 int /*<<< orphan*/  rds_ib_conn_error (struct rds_connection*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rds_ib_ring_completed (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rds_ib_ring_free (TYPE_3__*,scalar_t__) ; 
 scalar_t__ rds_ib_ring_oldest (TYPE_3__*) ; 
 struct rds_message* rds_ib_send_unmap_op (struct rds_ib_connection*,struct rds_ib_send_work*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_ib_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_ib_sub_signaled (struct rds_ib_connection*,int) ; 
 int /*<<< orphan*/  rds_message_put (struct rds_message*) ; 
 int /*<<< orphan*/  rds_message_unmapped (struct rds_message*) ; 
 int /*<<< orphan*/  rds_wq ; 
 int /*<<< orphan*/  rdsdebug (char*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_ib_tx_cq_event ; 
 int /*<<< orphan*/  s_ib_tx_stalled ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

void rds_ib_send_cqe_handler(struct rds_ib_connection *ic, struct ib_wc *wc)
{
	struct rds_message *rm = NULL;
	struct rds_connection *conn = ic->conn;
	struct rds_ib_send_work *send;
	u32 completed;
	u32 oldest;
	u32 i = 0;
	int nr_sig = 0;


	rdsdebug("wc wr_id 0x%llx status %u (%s) byte_len %u imm_data %u\n",
		 (unsigned long long)wc->wr_id, wc->status,
		 ib_wc_status_msg(wc->status), wc->byte_len,
		 be32_to_cpu(wc->ex.imm_data));
	rds_ib_stats_inc(s_ib_tx_cq_event);

	if (wc->wr_id == RDS_IB_ACK_WR_ID) {
		if (time_after(jiffies, ic->i_ack_queued + HZ / 2))
			rds_ib_stats_inc(s_ib_tx_stalled);
		rds_ib_ack_send_complete(ic);
		return;
	}

	oldest = rds_ib_ring_oldest(&ic->i_send_ring);

	completed = rds_ib_ring_completed(&ic->i_send_ring, wc->wr_id, oldest);

	for (i = 0; i < completed; i++) {
		send = &ic->i_sends[oldest];
		if (send->s_wr.send_flags & IB_SEND_SIGNALED)
			nr_sig++;

		rm = rds_ib_send_unmap_op(ic, send, wc->status);

		if (time_after(jiffies, send->s_queued + HZ / 2))
			rds_ib_stats_inc(s_ib_tx_stalled);

		if (send->s_op) {
			if (send->s_op == rm->m_final_op) {
				/* If anyone waited for this message to get
				 * flushed out, wake them up now
				 */
				rds_message_unmapped(rm);
			}
			rds_message_put(rm);
			send->s_op = NULL;
		}

		oldest = (oldest + 1) % ic->i_send_ring.w_nr;
	}

	rds_ib_ring_free(&ic->i_send_ring, completed);
	rds_ib_sub_signaled(ic, nr_sig);
	nr_sig = 0;

	if (test_and_clear_bit(RDS_LL_SEND_FULL, &conn->c_flags) ||
	    test_bit(0, &conn->c_map_queued))
		queue_delayed_work(rds_wq, &conn->c_send_w, 0);

	/* We expect errors as the qp is drained during shutdown */
	if (wc->status != IB_WC_SUCCESS && rds_conn_up(conn)) {
		rds_ib_conn_error(conn, "send completion on <%pI6c,%pI6c,%d> had status %u (%s), disconnecting and reconnecting\n",
				  &conn->c_laddr, &conn->c_faddr,
				  conn->c_tos, wc->status,
				  ib_wc_status_msg(wc->status));
	}
}
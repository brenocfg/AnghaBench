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
struct rds_ib_recv_work {TYPE_3__* r_frag; } ;
struct rds_ib_connection {int /*<<< orphan*/  i_recv_ring; TYPE_2__* i_cm_id; struct rds_ib_recv_work* i_recvs; struct rds_connection* conn; } ;
struct rds_ib_ack_state {int dummy; } ;
struct rds_connection {int /*<<< orphan*/  c_tos; int /*<<< orphan*/  c_faddr; int /*<<< orphan*/  c_laddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  imm_data; } ;
struct ib_wc {int /*<<< orphan*/  status; int /*<<< orphan*/  byte_len; TYPE_1__ ex; scalar_t__ wr_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  f_sg; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_wc_status_msg (int /*<<< orphan*/ ) ; 
 scalar_t__ rds_conn_connecting (struct rds_connection*) ; 
 scalar_t__ rds_conn_up (struct rds_connection*) ; 
 int /*<<< orphan*/  rds_ib_conn_error (struct rds_connection*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_ib_frag_free (struct rds_ib_connection*,TYPE_3__*) ; 
 int /*<<< orphan*/  rds_ib_process_recv (struct rds_connection*,struct rds_ib_recv_work*,int /*<<< orphan*/ ,struct rds_ib_ack_state*) ; 
 int /*<<< orphan*/  rds_ib_recv_refill (struct rds_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rds_ib_ring_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_ib_ring_free (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rds_ib_ring_low (int /*<<< orphan*/ *) ; 
 size_t rds_ib_ring_oldest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_ib_stats_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdsdebug (char*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s_ib_rx_cq_event ; 
 int /*<<< orphan*/  s_ib_rx_refill_from_cq ; 
 int /*<<< orphan*/  s_ib_rx_ring_empty ; 

void rds_ib_recv_cqe_handler(struct rds_ib_connection *ic,
			     struct ib_wc *wc,
			     struct rds_ib_ack_state *state)
{
	struct rds_connection *conn = ic->conn;
	struct rds_ib_recv_work *recv;

	rdsdebug("wc wr_id 0x%llx status %u (%s) byte_len %u imm_data %u\n",
		 (unsigned long long)wc->wr_id, wc->status,
		 ib_wc_status_msg(wc->status), wc->byte_len,
		 be32_to_cpu(wc->ex.imm_data));

	rds_ib_stats_inc(s_ib_rx_cq_event);
	recv = &ic->i_recvs[rds_ib_ring_oldest(&ic->i_recv_ring)];
	ib_dma_unmap_sg(ic->i_cm_id->device, &recv->r_frag->f_sg, 1,
			DMA_FROM_DEVICE);

	/* Also process recvs in connecting state because it is possible
	 * to get a recv completion _before_ the rdmacm ESTABLISHED
	 * event is processed.
	 */
	if (wc->status == IB_WC_SUCCESS) {
		rds_ib_process_recv(conn, recv, wc->byte_len, state);
	} else {
		/* We expect errors as the qp is drained during shutdown */
		if (rds_conn_up(conn) || rds_conn_connecting(conn))
			rds_ib_conn_error(conn, "recv completion on <%pI6c,%pI6c, %d> had status %u (%s), disconnecting and reconnecting\n",
					  &conn->c_laddr, &conn->c_faddr,
					  conn->c_tos, wc->status,
					  ib_wc_status_msg(wc->status));
	}

	/* rds_ib_process_recv() doesn't always consume the frag, and
	 * we might not have called it at all if the wc didn't indicate
	 * success. We already unmapped the frag's pages, though, and
	 * the following rds_ib_ring_free() call tells the refill path
	 * that it will not find an allocated frag here. Make sure we
	 * keep that promise by freeing a frag that's still on the ring.
	 */
	if (recv->r_frag) {
		rds_ib_frag_free(ic, recv->r_frag);
		recv->r_frag = NULL;
	}
	rds_ib_ring_free(&ic->i_recv_ring, 1);

	/* If we ever end up with a really empty receive ring, we're
	 * in deep trouble, as the sender will definitely see RNR
	 * timeouts. */
	if (rds_ib_ring_empty(&ic->i_recv_ring))
		rds_ib_stats_inc(s_ib_rx_ring_empty);

	if (rds_ib_ring_low(&ic->i_recv_ring)) {
		rds_ib_recv_refill(conn, 0, GFP_NOWAIT);
		rds_ib_stats_inc(s_ib_rx_refill_from_cq);
	}
}
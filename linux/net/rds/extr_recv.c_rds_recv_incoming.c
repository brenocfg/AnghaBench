#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct rds_sock {int /*<<< orphan*/  rs_recv_lock; int /*<<< orphan*/  rs_recv_queue; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx_tstamp; } ;
struct TYPE_9__ {scalar_t__ h_sport; scalar_t__ h_dport; int h_flags; int /*<<< orphan*/  h_len; int /*<<< orphan*/  h_sequence; } ;
struct rds_incoming {int /*<<< orphan*/  i_item; int /*<<< orphan*/ * i_rx_lat_trace; TYPE_2__ i_usercopy; TYPE_4__ i_hdr; struct rds_connection* i_conn; int /*<<< orphan*/  i_rx_jiffies; struct rds_conn_path* i_conn_path; } ;
struct rds_connection {int /*<<< orphan*/  c_lcong; int /*<<< orphan*/  c_bound_if; struct rds_conn_path* c_path; TYPE_1__* c_trans; } ;
struct rds_conn_path {scalar_t__ cp_next_rx_seq; TYPE_3__* cp_conn; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_8__ {int /*<<< orphan*/  c_hs_waitq; } ;
struct TYPE_6__ {scalar_t__ t_mp_capable; } ;

/* Variables and functions */
 scalar_t__ RDS_FLAG_PROBE_PORT ; 
 int RDS_FLAG_RETRANSMITTED ; 
 scalar_t__ RDS_HS_PROBE (scalar_t__,scalar_t__) ; 
 size_t RDS_MSG_RX_END ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  SOCK_RCVTSTAMP ; 
 int /*<<< orphan*/  __rds_wake_sk_sleep (struct sock*) ; 
 scalar_t__ be16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_clock () ; 
 struct rds_sock* rds_find_bound (struct in6_addr*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_inc_addref (struct rds_incoming*) ; 
 int /*<<< orphan*/  rds_recv_hs_exthdrs (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  rds_recv_incoming_exthdrs (struct rds_incoming*,struct rds_sock*) ; 
 int /*<<< orphan*/  rds_recv_rcvbuf_delta (struct rds_sock*,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sock* rds_rs_to_sk (struct rds_sock*) ; 
 int /*<<< orphan*/  rds_send_pong (struct rds_conn_path*,scalar_t__) ; 
 int /*<<< orphan*/  rds_sock_put (struct rds_sock*) ; 
 int /*<<< orphan*/  rds_start_mprds (TYPE_3__*) ; 
 int /*<<< orphan*/  rds_stats_inc (int /*<<< orphan*/ ) ; 
 scalar_t__ rds_sysctl_ping_enable ; 
 int /*<<< orphan*/  rdsdebug (char*,...) ; 
 int /*<<< orphan*/  s_recv_drop_dead_sock ; 
 int /*<<< orphan*/  s_recv_drop_no_sock ; 
 int /*<<< orphan*/  s_recv_drop_old_seq ; 
 int /*<<< orphan*/  s_recv_ping ; 
 int /*<<< orphan*/  s_recv_queued ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rds_recv_incoming(struct rds_connection *conn, struct in6_addr *saddr,
		       struct in6_addr *daddr,
		       struct rds_incoming *inc, gfp_t gfp)
{
	struct rds_sock *rs = NULL;
	struct sock *sk;
	unsigned long flags;
	struct rds_conn_path *cp;

	inc->i_conn = conn;
	inc->i_rx_jiffies = jiffies;
	if (conn->c_trans->t_mp_capable)
		cp = inc->i_conn_path;
	else
		cp = &conn->c_path[0];

	rdsdebug("conn %p next %llu inc %p seq %llu len %u sport %u dport %u "
		 "flags 0x%x rx_jiffies %lu\n", conn,
		 (unsigned long long)cp->cp_next_rx_seq,
		 inc,
		 (unsigned long long)be64_to_cpu(inc->i_hdr.h_sequence),
		 be32_to_cpu(inc->i_hdr.h_len),
		 be16_to_cpu(inc->i_hdr.h_sport),
		 be16_to_cpu(inc->i_hdr.h_dport),
		 inc->i_hdr.h_flags,
		 inc->i_rx_jiffies);

	/*
	 * Sequence numbers should only increase.  Messages get their
	 * sequence number as they're queued in a sending conn.  They
	 * can be dropped, though, if the sending socket is closed before
	 * they hit the wire.  So sequence numbers can skip forward
	 * under normal operation.  They can also drop back in the conn
	 * failover case as previously sent messages are resent down the
	 * new instance of a conn.  We drop those, otherwise we have
	 * to assume that the next valid seq does not come after a
	 * hole in the fragment stream.
	 *
	 * The headers don't give us a way to realize if fragments of
	 * a message have been dropped.  We assume that frags that arrive
	 * to a flow are part of the current message on the flow that is
	 * being reassembled.  This means that senders can't drop messages
	 * from the sending conn until all their frags are sent.
	 *
	 * XXX we could spend more on the wire to get more robust failure
	 * detection, arguably worth it to avoid data corruption.
	 */
	if (be64_to_cpu(inc->i_hdr.h_sequence) < cp->cp_next_rx_seq &&
	    (inc->i_hdr.h_flags & RDS_FLAG_RETRANSMITTED)) {
		rds_stats_inc(s_recv_drop_old_seq);
		goto out;
	}
	cp->cp_next_rx_seq = be64_to_cpu(inc->i_hdr.h_sequence) + 1;

	if (rds_sysctl_ping_enable && inc->i_hdr.h_dport == 0) {
		if (inc->i_hdr.h_sport == 0) {
			rdsdebug("ignore ping with 0 sport from %pI6c\n",
				 saddr);
			goto out;
		}
		rds_stats_inc(s_recv_ping);
		rds_send_pong(cp, inc->i_hdr.h_sport);
		/* if this is a handshake ping, start multipath if necessary */
		if (RDS_HS_PROBE(be16_to_cpu(inc->i_hdr.h_sport),
				 be16_to_cpu(inc->i_hdr.h_dport))) {
			rds_recv_hs_exthdrs(&inc->i_hdr, cp->cp_conn);
			rds_start_mprds(cp->cp_conn);
		}
		goto out;
	}

	if (be16_to_cpu(inc->i_hdr.h_dport) ==  RDS_FLAG_PROBE_PORT &&
	    inc->i_hdr.h_sport == 0) {
		rds_recv_hs_exthdrs(&inc->i_hdr, cp->cp_conn);
		/* if this is a handshake pong, start multipath if necessary */
		rds_start_mprds(cp->cp_conn);
		wake_up(&cp->cp_conn->c_hs_waitq);
		goto out;
	}

	rs = rds_find_bound(daddr, inc->i_hdr.h_dport, conn->c_bound_if);
	if (!rs) {
		rds_stats_inc(s_recv_drop_no_sock);
		goto out;
	}

	/* Process extension headers */
	rds_recv_incoming_exthdrs(inc, rs);

	/* We can be racing with rds_release() which marks the socket dead. */
	sk = rds_rs_to_sk(rs);

	/* serialize with rds_release -> sock_orphan */
	write_lock_irqsave(&rs->rs_recv_lock, flags);
	if (!sock_flag(sk, SOCK_DEAD)) {
		rdsdebug("adding inc %p to rs %p's recv queue\n", inc, rs);
		rds_stats_inc(s_recv_queued);
		rds_recv_rcvbuf_delta(rs, sk, inc->i_conn->c_lcong,
				      be32_to_cpu(inc->i_hdr.h_len),
				      inc->i_hdr.h_dport);
		if (sock_flag(sk, SOCK_RCVTSTAMP))
			inc->i_usercopy.rx_tstamp = ktime_get_real();
		rds_inc_addref(inc);
		inc->i_rx_lat_trace[RDS_MSG_RX_END] = local_clock();
		list_add_tail(&inc->i_item, &rs->rs_recv_queue);
		__rds_wake_sk_sleep(sk);
	} else {
		rds_stats_inc(s_recv_drop_dead_sock);
	}
	write_unlock_irqrestore(&rs->rs_recv_lock, flags);

out:
	if (rs)
		rds_sock_put(rs);
}
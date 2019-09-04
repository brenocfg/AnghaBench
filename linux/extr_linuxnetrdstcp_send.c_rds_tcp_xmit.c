#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct rds_tcp_connection {TYPE_7__* t_sock; scalar_t__ t_last_expected_una; scalar_t__ t_last_sent_nxt; } ;
struct TYPE_15__ {int op_nents; TYPE_8__* op_sg; } ;
struct TYPE_12__ {int /*<<< orphan*/  h_flags; int /*<<< orphan*/  h_len; } ;
struct TYPE_13__ {TYPE_3__ i_hdr; struct rds_conn_path* i_conn_path; } ;
struct rds_message {TYPE_6__ data; TYPE_4__ m_inc; scalar_t__ m_ack_seq; int /*<<< orphan*/  m_flags; } ;
struct rds_header {int dummy; } ;
struct rds_connection {int /*<<< orphan*/  c_faddr; } ;
struct rds_conn_path {int /*<<< orphan*/  cp_index; struct rds_tcp_connection* cp_transport_data; } ;
struct TYPE_17__ {unsigned int length; scalar_t__ offset; } ;
struct TYPE_16__ {TYPE_5__* ops; TYPE_2__* sk; } ;
struct TYPE_14__ {int (* sendpage ) (TYPE_7__*,scalar_t__,scalar_t__,unsigned int,int) ;} ;
struct TYPE_11__ {TYPE_1__* sk_socket; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 int MSG_DONTWAIT ; 
 int MSG_MORE ; 
 int MSG_NOSIGNAL ; 
 int MSG_SENDPAGE_NOTLAST ; 
 int /*<<< orphan*/  RDS_FLAG_RETRANSMITTED ; 
 int /*<<< orphan*/  RDS_MSG_HAS_ACK_SEQ ; 
 int /*<<< orphan*/  RDS_MSG_RETRANSMITTED ; 
 int /*<<< orphan*/  SOCK_NOSPACE ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rds_conn_path_drop (struct rds_conn_path*,int) ; 
 scalar_t__ rds_conn_path_up (struct rds_conn_path*) ; 
 int rds_tcp_sendmsg (TYPE_7__*,void*,int) ; 
 int /*<<< orphan*/  rds_tcp_stats_inc (int /*<<< orphan*/ ) ; 
 scalar_t__ rds_tcp_write_seq (struct rds_tcp_connection*) ; 
 int /*<<< orphan*/  rdsdebug (char*,void*,scalar_t__,unsigned int,...) ; 
 int /*<<< orphan*/  s_tcp_sndbuf_full ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sg_page (TYPE_8__*) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 int stub1 (TYPE_7__*,scalar_t__,scalar_t__,unsigned int,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rds_tcp_xmit(struct rds_connection *conn, struct rds_message *rm,
		 unsigned int hdr_off, unsigned int sg, unsigned int off)
{
	struct rds_conn_path *cp = rm->m_inc.i_conn_path;
	struct rds_tcp_connection *tc = cp->cp_transport_data;
	int done = 0;
	int ret = 0;
	int more;

	if (hdr_off == 0) {
		/*
		 * m_ack_seq is set to the sequence number of the last byte of
		 * header and data.  see rds_tcp_is_acked().
		 */
		tc->t_last_sent_nxt = rds_tcp_write_seq(tc);
		rm->m_ack_seq = tc->t_last_sent_nxt +
				sizeof(struct rds_header) +
				be32_to_cpu(rm->m_inc.i_hdr.h_len) - 1;
		smp_mb__before_atomic();
		set_bit(RDS_MSG_HAS_ACK_SEQ, &rm->m_flags);
		tc->t_last_expected_una = rm->m_ack_seq + 1;

		if (test_bit(RDS_MSG_RETRANSMITTED, &rm->m_flags))
			rm->m_inc.i_hdr.h_flags |= RDS_FLAG_RETRANSMITTED;

		rdsdebug("rm %p tcp nxt %u ack_seq %llu\n",
			 rm, rds_tcp_write_seq(tc),
			 (unsigned long long)rm->m_ack_seq);
	}

	if (hdr_off < sizeof(struct rds_header)) {
		/* see rds_tcp_write_space() */
		set_bit(SOCK_NOSPACE, &tc->t_sock->sk->sk_socket->flags);

		ret = rds_tcp_sendmsg(tc->t_sock,
				      (void *)&rm->m_inc.i_hdr + hdr_off,
				      sizeof(rm->m_inc.i_hdr) - hdr_off);
		if (ret < 0)
			goto out;
		done += ret;
		if (hdr_off + done != sizeof(struct rds_header))
			goto out;
	}

	more = rm->data.op_nents > 1 ? (MSG_MORE | MSG_SENDPAGE_NOTLAST) : 0;
	while (sg < rm->data.op_nents) {
		int flags = MSG_DONTWAIT | MSG_NOSIGNAL | more;

		ret = tc->t_sock->ops->sendpage(tc->t_sock,
						sg_page(&rm->data.op_sg[sg]),
						rm->data.op_sg[sg].offset + off,
						rm->data.op_sg[sg].length - off,
						flags);
		rdsdebug("tcp sendpage %p:%u:%u ret %d\n", (void *)sg_page(&rm->data.op_sg[sg]),
			 rm->data.op_sg[sg].offset + off, rm->data.op_sg[sg].length - off,
			 ret);
		if (ret <= 0)
			break;

		off += ret;
		done += ret;
		if (off == rm->data.op_sg[sg].length) {
			off = 0;
			sg++;
		}
		if (sg == rm->data.op_nents - 1)
			more = 0;
	}

out:
	if (ret <= 0) {
		/* write_space will hit after EAGAIN, all else fatal */
		if (ret == -EAGAIN) {
			rds_tcp_stats_inc(s_tcp_sndbuf_full);
			ret = 0;
		} else {
			/* No need to disconnect/reconnect if path_drop
			 * has already been triggered, because, e.g., of
			 * an incoming RST.
			 */
			if (rds_conn_path_up(cp)) {
				pr_warn("RDS/tcp: send to %pI6c on cp [%d]"
					"returned %d, "
					"disconnecting and reconnecting\n",
					&conn->c_faddr, cp->cp_index, ret);
				rds_conn_path_drop(cp, false);
			}
		}
	}
	if (done == 0)
		done = ret;
	return done;
}
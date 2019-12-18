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
typedef  int u32 ;
struct rds_sock {int rs_snd_bytes; int /*<<< orphan*/  rs_lock; int /*<<< orphan*/  rs_send_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  h_sequence; int /*<<< orphan*/  h_len; } ;
struct TYPE_3__ {TYPE_2__ i_hdr; struct rds_conn_path* i_conn_path; struct rds_connection* i_conn; } ;
struct rds_message {TYPE_1__ m_inc; int /*<<< orphan*/  m_flags; int /*<<< orphan*/  m_conn_item; struct rds_sock* m_rs; int /*<<< orphan*/  m_sock_item; } ;
struct rds_connection {int dummy; } ;
struct rds_conn_path {int /*<<< orphan*/  cp_lock; int /*<<< orphan*/  cp_send_queue; int /*<<< orphan*/  cp_next_tx_seq; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_MSG_ACK_REQUIRED ; 
 int /*<<< orphan*/  RDS_MSG_ON_CONN ; 
 int /*<<< orphan*/  RDS_MSG_ON_SOCK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_message_addref (struct rds_message*) ; 
 int /*<<< orphan*/  rds_message_populate_header (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_rs_to_sk (struct rds_sock*) ; 
 int rds_sk_sndbuf (struct rds_sock*) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_message*,int,struct rds_sock*,int,unsigned long long) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int rds_send_queue_rm(struct rds_sock *rs, struct rds_connection *conn,
			     struct rds_conn_path *cp,
			     struct rds_message *rm, __be16 sport,
			     __be16 dport, int *queued)
{
	unsigned long flags;
	u32 len;

	if (*queued)
		goto out;

	len = be32_to_cpu(rm->m_inc.i_hdr.h_len);

	/* this is the only place which holds both the socket's rs_lock
	 * and the connection's c_lock */
	spin_lock_irqsave(&rs->rs_lock, flags);

	/*
	 * If there is a little space in sndbuf, we don't queue anything,
	 * and userspace gets -EAGAIN. But poll() indicates there's send
	 * room. This can lead to bad behavior (spinning) if snd_bytes isn't
	 * freed up by incoming acks. So we check the *old* value of
	 * rs_snd_bytes here to allow the last msg to exceed the buffer,
	 * and poll() now knows no more data can be sent.
	 */
	if (rs->rs_snd_bytes < rds_sk_sndbuf(rs)) {
		rs->rs_snd_bytes += len;

		/* let recv side know we are close to send space exhaustion.
		 * This is probably not the optimal way to do it, as this
		 * means we set the flag on *all* messages as soon as our
		 * throughput hits a certain threshold.
		 */
		if (rs->rs_snd_bytes >= rds_sk_sndbuf(rs) / 2)
			set_bit(RDS_MSG_ACK_REQUIRED, &rm->m_flags);

		list_add_tail(&rm->m_sock_item, &rs->rs_send_queue);
		set_bit(RDS_MSG_ON_SOCK, &rm->m_flags);
		rds_message_addref(rm);
		sock_hold(rds_rs_to_sk(rs));
		rm->m_rs = rs;

		/* The code ordering is a little weird, but we're
		   trying to minimize the time we hold c_lock */
		rds_message_populate_header(&rm->m_inc.i_hdr, sport, dport, 0);
		rm->m_inc.i_conn = conn;
		rm->m_inc.i_conn_path = cp;
		rds_message_addref(rm);

		spin_lock(&cp->cp_lock);
		rm->m_inc.i_hdr.h_sequence = cpu_to_be64(cp->cp_next_tx_seq++);
		list_add_tail(&rm->m_conn_item, &cp->cp_send_queue);
		set_bit(RDS_MSG_ON_CONN, &rm->m_flags);
		spin_unlock(&cp->cp_lock);

		rdsdebug("queued msg %p len %d, rs %p bytes %d seq %llu\n",
			 rm, len, rs, rs->rs_snd_bytes,
			 (unsigned long long)be64_to_cpu(rm->m_inc.i_hdr.h_sequence));

		*queued = 1;
	}

	spin_unlock_irqrestore(&rs->rs_lock, flags);
out:
	return *queued;
}
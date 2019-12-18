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
struct sock {void (* sk_state_change ) (struct sock*) ;int sk_state; int /*<<< orphan*/  sk_callback_lock; struct rds_conn_path* sk_user_data; } ;
struct rds_tcp_connection {void (* t_orig_state_change ) (struct sock*) ;int /*<<< orphan*/  t_sock; } ;
struct rds_conn_path {TYPE_1__* cp_conn; struct rds_tcp_connection* cp_transport_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  c_faddr; int /*<<< orphan*/  c_laddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_CONN_CONNECTING ; 
 int /*<<< orphan*/  RDS_CONN_ERROR ; 
#define  TCP_CLOSE 132 
#define  TCP_CLOSE_WAIT 131 
#define  TCP_ESTABLISHED 130 
#define  TCP_SYN_RECV 129 
#define  TCP_SYN_SENT 128 
 int /*<<< orphan*/  rds_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_conn_path_drop (struct rds_conn_path*,int) ; 
 int /*<<< orphan*/  rds_conn_path_transition (struct rds_conn_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_connect_path_complete (struct rds_conn_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdsdebug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

void rds_tcp_state_change(struct sock *sk)
{
	void (*state_change)(struct sock *sk);
	struct rds_conn_path *cp;
	struct rds_tcp_connection *tc;

	read_lock_bh(&sk->sk_callback_lock);
	cp = sk->sk_user_data;
	if (!cp) {
		state_change = sk->sk_state_change;
		goto out;
	}
	tc = cp->cp_transport_data;
	state_change = tc->t_orig_state_change;

	rdsdebug("sock %p state_change to %d\n", tc->t_sock, sk->sk_state);

	switch (sk->sk_state) {
	/* ignore connecting sockets as they make progress */
	case TCP_SYN_SENT:
	case TCP_SYN_RECV:
		break;
	case TCP_ESTABLISHED:
		/* Force the peer to reconnect so that we have the
		 * TCP ports going from <smaller-ip>.<transient> to
		 * <larger-ip>.<RDS_TCP_PORT>. We avoid marking the
		 * RDS connection as RDS_CONN_UP until the reconnect,
		 * to avoid RDS datagram loss.
		 */
		if (rds_addr_cmp(&cp->cp_conn->c_laddr,
				 &cp->cp_conn->c_faddr) >= 0 &&
		    rds_conn_path_transition(cp, RDS_CONN_CONNECTING,
					     RDS_CONN_ERROR)) {
			rds_conn_path_drop(cp, false);
		} else {
			rds_connect_path_complete(cp, RDS_CONN_CONNECTING);
		}
		break;
	case TCP_CLOSE_WAIT:
	case TCP_CLOSE:
		rds_conn_path_drop(cp, false);
	default:
		break;
	}
out:
	read_unlock_bh(&sk->sk_callback_lock);
	state_change(sk);
}
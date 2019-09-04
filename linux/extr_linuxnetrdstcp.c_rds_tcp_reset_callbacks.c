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
struct socket {int /*<<< orphan*/  sk; } ;
struct rds_tcp_connection {int t_tinc_hdr_rem; scalar_t__ t_tinc_data_rem; TYPE_1__* t_tinc; struct socket* t_sock; } ;
struct rds_header {int dummy; } ;
struct rds_conn_path {int /*<<< orphan*/  cp_recv_w; int /*<<< orphan*/  cp_send_w; int /*<<< orphan*/  cp_flags; int /*<<< orphan*/  cp_waitq; int /*<<< orphan*/  cp_state; struct rds_tcp_connection* cp_transport_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  ti_inc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_CONN_RESETTING ; 
 int /*<<< orphan*/  RDS_IN_XMIT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_inc_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_send_path_reset (struct rds_conn_path*) ; 
 int /*<<< orphan*/  rds_tcp_restore_callbacks (struct socket*,struct rds_tcp_connection*) ; 
 int /*<<< orphan*/  rds_tcp_set_callbacks (struct socket*,struct rds_conn_path*) ; 
 int /*<<< orphan*/  release_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void rds_tcp_reset_callbacks(struct socket *sock,
			     struct rds_conn_path *cp)
{
	struct rds_tcp_connection *tc = cp->cp_transport_data;
	struct socket *osock = tc->t_sock;

	if (!osock)
		goto newsock;

	/* Need to resolve a duelling SYN between peers.
	 * We have an outstanding SYN to this peer, which may
	 * potentially have transitioned to the RDS_CONN_UP state,
	 * so we must quiesce any send threads before resetting
	 * cp_transport_data. We quiesce these threads by setting
	 * cp_state to something other than RDS_CONN_UP, and then
	 * waiting for any existing threads in rds_send_xmit to
	 * complete release_in_xmit(). (Subsequent threads entering
	 * rds_send_xmit() will bail on !rds_conn_up().
	 *
	 * However an incoming syn-ack at this point would end up
	 * marking the conn as RDS_CONN_UP, and would again permit
	 * rds_send_xmi() threads through, so ideally we would
	 * synchronize on RDS_CONN_UP after lock_sock(), but cannot
	 * do that: waiting on !RDS_IN_XMIT after lock_sock() may
	 * end up deadlocking with tcp_sendmsg(), and the RDS_IN_XMIT
	 * would not get set. As a result, we set c_state to
	 * RDS_CONN_RESETTTING, to ensure that rds_tcp_state_change
	 * cannot mark rds_conn_path_up() in the window before lock_sock()
	 */
	atomic_set(&cp->cp_state, RDS_CONN_RESETTING);
	wait_event(cp->cp_waitq, !test_bit(RDS_IN_XMIT, &cp->cp_flags));
	lock_sock(osock->sk);
	/* reset receive side state for rds_tcp_data_recv() for osock  */
	cancel_delayed_work_sync(&cp->cp_send_w);
	cancel_delayed_work_sync(&cp->cp_recv_w);
	if (tc->t_tinc) {
		rds_inc_put(&tc->t_tinc->ti_inc);
		tc->t_tinc = NULL;
	}
	tc->t_tinc_hdr_rem = sizeof(struct rds_header);
	tc->t_tinc_data_rem = 0;
	rds_tcp_restore_callbacks(osock, tc);
	release_sock(osock->sk);
	sock_release(osock);
newsock:
	rds_send_path_reset(cp);
	lock_sock(sock->sk);
	rds_tcp_set_callbacks(sock, cp);
	release_sock(sock->sk);
}
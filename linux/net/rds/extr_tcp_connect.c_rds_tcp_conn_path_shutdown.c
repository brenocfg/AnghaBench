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
struct socket {int /*<<< orphan*/  sk; TYPE_1__* ops; } ;
struct rds_tcp_connection {int t_tinc_hdr_rem; scalar_t__ t_tinc_data_rem; TYPE_2__* t_tinc; struct socket* t_sock; } ;
struct rds_header {int dummy; } ;
struct rds_conn_path {int /*<<< orphan*/  cp_conn; struct rds_tcp_connection* cp_transport_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  ti_inc; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* shutdown ) (struct socket*,int) ;} ;

/* Variables and functions */
 int RCV_SHUTDOWN ; 
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  lock_sock (int /*<<< orphan*/ ) ; 
 scalar_t__ rds_destroy_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_inc_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_tcp_restore_callbacks (struct socket*,struct rds_tcp_connection*) ; 
 int /*<<< orphan*/  rds_tcp_set_linger (struct socket*) ; 
 int /*<<< orphan*/  rdsdebug (char*,int /*<<< orphan*/ ,struct rds_tcp_connection*,struct socket*) ; 
 int /*<<< orphan*/  release_sock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int /*<<< orphan*/  stub1 (struct socket*,int) ; 

void rds_tcp_conn_path_shutdown(struct rds_conn_path *cp)
{
	struct rds_tcp_connection *tc = cp->cp_transport_data;
	struct socket *sock = tc->t_sock;

	rdsdebug("shutting down conn %p tc %p sock %p\n",
		 cp->cp_conn, tc, sock);

	if (sock) {
		if (rds_destroy_pending(cp->cp_conn))
			rds_tcp_set_linger(sock);
		sock->ops->shutdown(sock, RCV_SHUTDOWN | SEND_SHUTDOWN);
		lock_sock(sock->sk);
		rds_tcp_restore_callbacks(sock, tc); /* tc->tc_sock = NULL */

		release_sock(sock->sk);
		sock_release(sock);
	}

	if (tc->t_tinc) {
		rds_inc_put(&tc->t_tinc->ti_inc);
		tc->t_tinc = NULL;
	}
	tc->t_tinc_hdr_rem = sizeof(struct rds_header);
	tc->t_tinc_data_rem = 0;
}
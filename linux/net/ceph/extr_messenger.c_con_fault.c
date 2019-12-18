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
struct ceph_connection {scalar_t__ state; int delay; int /*<<< orphan*/  out_queue; int /*<<< orphan*/  out_sent; TYPE_1__* in_msg; int /*<<< orphan*/ * error_msg; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  peer_name; } ;
struct TYPE_2__ {struct ceph_connection* con; } ;

/* Variables and functions */
 int BASE_DELAY_INTERVAL ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CON_FLAG_BACKOFF ; 
 int /*<<< orphan*/  CON_FLAG_KEEPALIVE_PENDING ; 
 int /*<<< orphan*/  CON_FLAG_LOSSYTX ; 
 int /*<<< orphan*/  CON_FLAG_WRITE_PENDING ; 
 scalar_t__ CON_STATE_CLOSED ; 
 scalar_t__ CON_STATE_CONNECTING ; 
 scalar_t__ CON_STATE_NEGOTIATING ; 
 scalar_t__ CON_STATE_OPEN ; 
 scalar_t__ CON_STATE_PREOPEN ; 
 scalar_t__ CON_STATE_STANDBY ; 
 int /*<<< orphan*/  ENTITY_NAME (int /*<<< orphan*/ ) ; 
 int MAX_DELAY_INTERVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ceph_msg_put (TYPE_1__*) ; 
 int /*<<< orphan*/  ceph_pr_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  con_close_socket (struct ceph_connection*) ; 
 int /*<<< orphan*/  con_flag_clear (struct ceph_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  con_flag_set (struct ceph_connection*,int /*<<< orphan*/ ) ; 
 scalar_t__ con_flag_test (struct ceph_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_con (struct ceph_connection*) ; 

__attribute__((used)) static void con_fault(struct ceph_connection *con)
{
	dout("fault %p state %lu to peer %s\n",
	     con, con->state, ceph_pr_addr(&con->peer_addr));

	pr_warn("%s%lld %s %s\n", ENTITY_NAME(con->peer_name),
		ceph_pr_addr(&con->peer_addr), con->error_msg);
	con->error_msg = NULL;

	WARN_ON(con->state != CON_STATE_CONNECTING &&
	       con->state != CON_STATE_NEGOTIATING &&
	       con->state != CON_STATE_OPEN);

	con_close_socket(con);

	if (con_flag_test(con, CON_FLAG_LOSSYTX)) {
		dout("fault on LOSSYTX channel, marking CLOSED\n");
		con->state = CON_STATE_CLOSED;
		return;
	}

	if (con->in_msg) {
		BUG_ON(con->in_msg->con != con);
		ceph_msg_put(con->in_msg);
		con->in_msg = NULL;
	}

	/* Requeue anything that hasn't been acked */
	list_splice_init(&con->out_sent, &con->out_queue);

	/* If there are no messages queued or keepalive pending, place
	 * the connection in a STANDBY state */
	if (list_empty(&con->out_queue) &&
	    !con_flag_test(con, CON_FLAG_KEEPALIVE_PENDING)) {
		dout("fault %p setting STANDBY clearing WRITE_PENDING\n", con);
		con_flag_clear(con, CON_FLAG_WRITE_PENDING);
		con->state = CON_STATE_STANDBY;
	} else {
		/* retry after a delay. */
		con->state = CON_STATE_PREOPEN;
		if (con->delay == 0)
			con->delay = BASE_DELAY_INTERVAL;
		else if (con->delay < MAX_DELAY_INTERVAL)
			con->delay *= 2;
		con_flag_set(con, CON_FLAG_BACKOFF);
		queue_con(con);
	}
}
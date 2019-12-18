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
struct ceph_connection {int /*<<< orphan*/  mutex; scalar_t__ peer_global_seq; int /*<<< orphan*/  state; int /*<<< orphan*/  peer_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_FLAG_BACKOFF ; 
 int /*<<< orphan*/  CON_FLAG_KEEPALIVE_PENDING ; 
 int /*<<< orphan*/  CON_FLAG_LOSSYTX ; 
 int /*<<< orphan*/  CON_FLAG_WRITE_PENDING ; 
 int /*<<< orphan*/  CON_STATE_CLOSED ; 
 int /*<<< orphan*/  cancel_con (struct ceph_connection*) ; 
 int /*<<< orphan*/  ceph_pr_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  con_close_socket (struct ceph_connection*) ; 
 int /*<<< orphan*/  con_flag_clear (struct ceph_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_connection (struct ceph_connection*) ; 

void ceph_con_close(struct ceph_connection *con)
{
	mutex_lock(&con->mutex);
	dout("con_close %p peer %s\n", con, ceph_pr_addr(&con->peer_addr));
	con->state = CON_STATE_CLOSED;

	con_flag_clear(con, CON_FLAG_LOSSYTX);	/* so we retry next connect */
	con_flag_clear(con, CON_FLAG_KEEPALIVE_PENDING);
	con_flag_clear(con, CON_FLAG_WRITE_PENDING);
	con_flag_clear(con, CON_FLAG_BACKOFF);

	reset_connection(con);
	con->peer_global_seq = 0;
	cancel_con(con);
	con_close_socket(con);
	mutex_unlock(&con->mutex);
}
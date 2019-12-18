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
struct ceph_messenger {int dummy; } ;
struct ceph_connection_operations {int dummy; } ;
struct ceph_connection {int /*<<< orphan*/  state; int /*<<< orphan*/  work; int /*<<< orphan*/  out_sent; int /*<<< orphan*/  out_queue; int /*<<< orphan*/  mutex; struct ceph_messenger* msgr; struct ceph_connection_operations const* ops; void* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_STATE_CLOSED ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_con_workfn ; 
 int /*<<< orphan*/  con_sock_state_init (struct ceph_connection*) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_connection*) ; 
 int /*<<< orphan*/  memset (struct ceph_connection*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void ceph_con_init(struct ceph_connection *con, void *private,
	const struct ceph_connection_operations *ops,
	struct ceph_messenger *msgr)
{
	dout("con_init %p\n", con);
	memset(con, 0, sizeof(*con));
	con->private = private;
	con->ops = ops;
	con->msgr = msgr;

	con_sock_state_init(con);

	mutex_init(&con->mutex);
	INIT_LIST_HEAD(&con->out_queue);
	INIT_LIST_HEAD(&con->out_sent);
	INIT_DELAYED_WORK(&con->work, ceph_con_workfn);

	con->state = CON_STATE_CLOSED;
}
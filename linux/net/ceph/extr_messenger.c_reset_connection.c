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
struct ceph_connection {scalar_t__ out_skip; scalar_t__ in_seq_acked; scalar_t__ in_seq; TYPE_1__* out_msg; scalar_t__ out_seq; scalar_t__ connect_seq; TYPE_1__* in_msg; int /*<<< orphan*/  out_sent; int /*<<< orphan*/  out_queue; } ;
struct TYPE_2__ {struct ceph_connection* con; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ceph_msg_put (TYPE_1__*) ; 
 int /*<<< orphan*/  ceph_msg_remove_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_connection*) ; 

__attribute__((used)) static void reset_connection(struct ceph_connection *con)
{
	/* reset connection, out_queue, msg_ and connect_seq */
	/* discard existing out_queue and msg_seq */
	dout("reset_connection %p\n", con);
	ceph_msg_remove_list(&con->out_queue);
	ceph_msg_remove_list(&con->out_sent);

	if (con->in_msg) {
		BUG_ON(con->in_msg->con != con);
		ceph_msg_put(con->in_msg);
		con->in_msg = NULL;
	}

	con->connect_seq = 0;
	con->out_seq = 0;
	if (con->out_msg) {
		BUG_ON(con->out_msg->con != con);
		ceph_msg_put(con->out_msg);
		con->out_msg = NULL;
	}
	con->in_seq = 0;
	con->in_seq_acked = 0;

	con->out_skip = 0;
}
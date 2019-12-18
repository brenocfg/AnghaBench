#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data_len; int /*<<< orphan*/  middle_len; int /*<<< orphan*/  front_len; int /*<<< orphan*/  type; int /*<<< orphan*/  src; } ;
struct TYPE_7__ {scalar_t__ iov_len; } ;
struct ceph_msg {int needs_out_seq; TYPE_4__ hdr; int /*<<< orphan*/  list_head; TYPE_3__ front; } ;
struct ceph_connection {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  peer_name; int /*<<< orphan*/  out_queue; TYPE_2__* msgr; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__ inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CON_FLAG_WRITE_PENDING ; 
 scalar_t__ CON_STATE_CLOSED ; 
 int /*<<< orphan*/  ENTITY_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_msg_put (struct ceph_msg*) ; 
 int /*<<< orphan*/  ceph_msg_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_standby (struct ceph_connection*) ; 
 scalar_t__ con_flag_test_and_set (struct ceph_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,...) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_con_set (struct ceph_msg*,struct ceph_connection*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_con (struct ceph_connection*) ; 

void ceph_con_send(struct ceph_connection *con, struct ceph_msg *msg)
{
	/* set src+dst */
	msg->hdr.src = con->msgr->inst.name;
	BUG_ON(msg->front.iov_len != le32_to_cpu(msg->hdr.front_len));
	msg->needs_out_seq = true;

	mutex_lock(&con->mutex);

	if (con->state == CON_STATE_CLOSED) {
		dout("con_send %p closed, dropping %p\n", con, msg);
		ceph_msg_put(msg);
		mutex_unlock(&con->mutex);
		return;
	}

	msg_con_set(msg, con);

	BUG_ON(!list_empty(&msg->list_head));
	list_add_tail(&msg->list_head, &con->out_queue);
	dout("----- %p to %s%lld %d=%s len %d+%d+%d -----\n", msg,
	     ENTITY_NAME(con->peer_name), le16_to_cpu(msg->hdr.type),
	     ceph_msg_type_name(le16_to_cpu(msg->hdr.type)),
	     le32_to_cpu(msg->hdr.front_len),
	     le32_to_cpu(msg->hdr.middle_len),
	     le32_to_cpu(msg->hdr.data_len));

	clear_standby(con);
	mutex_unlock(&con->mutex);

	/* if there wasn't anything waiting to send before, queue
	 * new work */
	if (con_flag_test_and_set(con, CON_FLAG_WRITE_PENDING) == 0)
		queue_con(con);
}
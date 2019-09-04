#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/  data_len; int /*<<< orphan*/  front_len; int /*<<< orphan*/  type; TYPE_3__ src; int /*<<< orphan*/  seq; } ;
struct ceph_msg {TYPE_1__ hdr; struct ceph_connection* con; } ;
struct ceph_connection {int /*<<< orphan*/  mutex; TYPE_2__* ops; int /*<<< orphan*/  in_data_crc; int /*<<< orphan*/  in_middle_crc; int /*<<< orphan*/  in_front_crc; int /*<<< orphan*/  in_seq; TYPE_3__ peer_name; struct ceph_msg* in_msg; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* dispatch ) (struct ceph_connection*,struct ceph_msg*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ENTITY_NAME (TYPE_3__) ; 
 int /*<<< orphan*/  ceph_msg_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ceph_connection*,struct ceph_msg*) ; 

__attribute__((used)) static void process_message(struct ceph_connection *con)
{
	struct ceph_msg *msg = con->in_msg;

	BUG_ON(con->in_msg->con != con);
	con->in_msg = NULL;

	/* if first message, set peer_name */
	if (con->peer_name.type == 0)
		con->peer_name = msg->hdr.src;

	con->in_seq++;
	mutex_unlock(&con->mutex);

	dout("===== %p %llu from %s%lld %d=%s len %d+%d (%u %u %u) =====\n",
	     msg, le64_to_cpu(msg->hdr.seq),
	     ENTITY_NAME(msg->hdr.src),
	     le16_to_cpu(msg->hdr.type),
	     ceph_msg_type_name(le16_to_cpu(msg->hdr.type)),
	     le32_to_cpu(msg->hdr.front_len),
	     le32_to_cpu(msg->hdr.data_len),
	     con->in_front_crc, con->in_middle_crc, con->in_data_crc);
	con->ops->dispatch(con, msg);

	mutex_lock(&con->mutex);
}
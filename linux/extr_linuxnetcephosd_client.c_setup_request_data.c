#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ceph_osd_request {int r_num_ops; struct ceph_msg* r_reply; struct ceph_osd_req_op* r_ops; } ;
struct TYPE_12__ {int /*<<< orphan*/  response_data; int /*<<< orphan*/  request_data; } ;
struct TYPE_11__ {scalar_t__ class_len; scalar_t__ method_len; scalar_t__ indata_len; int /*<<< orphan*/  response_data; int /*<<< orphan*/  request_data; int /*<<< orphan*/  request_info; } ;
struct TYPE_10__ {int /*<<< orphan*/  response_data; } ;
struct TYPE_9__ {scalar_t__ length; int /*<<< orphan*/  osd_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  request_data; } ;
struct TYPE_7__ {scalar_t__ name_len; scalar_t__ value_len; int /*<<< orphan*/  osd_data; } ;
struct ceph_osd_req_op {int op; scalar_t__ indata_len; TYPE_6__ notify; TYPE_5__ cls; TYPE_4__ list_watchers; TYPE_3__ extent; int /*<<< orphan*/  raw_data_in; TYPE_2__ notify_ack; TYPE_1__ xattr; } ;
struct ceph_msg {int data_length; int /*<<< orphan*/  data; } ;

/* Variables and functions */
#define  CEPH_OSD_OP_CALL 137 
#define  CEPH_OSD_OP_CMPXATTR 136 
#define  CEPH_OSD_OP_LIST_WATCHERS 135 
#define  CEPH_OSD_OP_NOTIFY 134 
#define  CEPH_OSD_OP_NOTIFY_ACK 133 
#define  CEPH_OSD_OP_READ 132 
#define  CEPH_OSD_OP_SETXATTR 131 
#define  CEPH_OSD_OP_STAT 130 
#define  CEPH_OSD_OP_WRITE 129 
#define  CEPH_OSD_OP_WRITEFULL 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ceph_osdc_msg_data_add (struct ceph_msg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setup_request_data(struct ceph_osd_request *req,
			       struct ceph_msg *msg)
{
	u32 data_len = 0;
	int i;

	if (!list_empty(&msg->data))
		return;

	WARN_ON(msg->data_length);
	for (i = 0; i < req->r_num_ops; i++) {
		struct ceph_osd_req_op *op = &req->r_ops[i];

		switch (op->op) {
		/* request */
		case CEPH_OSD_OP_WRITE:
		case CEPH_OSD_OP_WRITEFULL:
			WARN_ON(op->indata_len != op->extent.length);
			ceph_osdc_msg_data_add(msg, &op->extent.osd_data);
			break;
		case CEPH_OSD_OP_SETXATTR:
		case CEPH_OSD_OP_CMPXATTR:
			WARN_ON(op->indata_len != op->xattr.name_len +
						  op->xattr.value_len);
			ceph_osdc_msg_data_add(msg, &op->xattr.osd_data);
			break;
		case CEPH_OSD_OP_NOTIFY_ACK:
			ceph_osdc_msg_data_add(msg,
					       &op->notify_ack.request_data);
			break;

		/* reply */
		case CEPH_OSD_OP_STAT:
			ceph_osdc_msg_data_add(req->r_reply,
					       &op->raw_data_in);
			break;
		case CEPH_OSD_OP_READ:
			ceph_osdc_msg_data_add(req->r_reply,
					       &op->extent.osd_data);
			break;
		case CEPH_OSD_OP_LIST_WATCHERS:
			ceph_osdc_msg_data_add(req->r_reply,
					       &op->list_watchers.response_data);
			break;

		/* both */
		case CEPH_OSD_OP_CALL:
			WARN_ON(op->indata_len != op->cls.class_len +
						  op->cls.method_len +
						  op->cls.indata_len);
			ceph_osdc_msg_data_add(msg, &op->cls.request_info);
			/* optional, can be NONE */
			ceph_osdc_msg_data_add(msg, &op->cls.request_data);
			/* optional, can be NONE */
			ceph_osdc_msg_data_add(req->r_reply,
					       &op->cls.response_data);
			break;
		case CEPH_OSD_OP_NOTIFY:
			ceph_osdc_msg_data_add(msg,
					       &op->notify.request_data);
			ceph_osdc_msg_data_add(req->r_reply,
					       &op->notify.response_data);
			break;
		}

		data_len += op->indata_len;
	}

	WARN_ON(data_len != msg->data_length);
}
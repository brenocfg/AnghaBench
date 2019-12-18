#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ceph_osd_request {unsigned int r_num_ops; struct ceph_osd_req_op* r_ops; } ;
struct TYPE_14__ {int /*<<< orphan*/  osd_data; } ;
struct TYPE_13__ {int /*<<< orphan*/  response_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  response_data; int /*<<< orphan*/  request_data; } ;
struct TYPE_11__ {int /*<<< orphan*/  request_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  osd_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  response_data; int /*<<< orphan*/  request_data; int /*<<< orphan*/  request_info; } ;
struct TYPE_8__ {int /*<<< orphan*/  osd_data; } ;
struct ceph_osd_req_op {int op; TYPE_7__ copy_from; TYPE_6__ list_watchers; TYPE_5__ notify; TYPE_4__ notify_ack; int /*<<< orphan*/  raw_data_in; TYPE_3__ xattr; TYPE_2__ cls; TYPE_1__ extent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  CEPH_OSD_OP_CALL 138 
#define  CEPH_OSD_OP_CMPXATTR 137 
#define  CEPH_OSD_OP_COPY_FROM 136 
#define  CEPH_OSD_OP_LIST_WATCHERS 135 
#define  CEPH_OSD_OP_NOTIFY 134 
#define  CEPH_OSD_OP_NOTIFY_ACK 133 
#define  CEPH_OSD_OP_READ 132 
#define  CEPH_OSD_OP_SETXATTR 131 
#define  CEPH_OSD_OP_STAT 130 
#define  CEPH_OSD_OP_WRITE 129 
#define  CEPH_OSD_OP_WRITEFULL 128 
 int /*<<< orphan*/  ceph_osd_data_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void osd_req_op_data_release(struct ceph_osd_request *osd_req,
			unsigned int which)
{
	struct ceph_osd_req_op *op;

	BUG_ON(which >= osd_req->r_num_ops);
	op = &osd_req->r_ops[which];

	switch (op->op) {
	case CEPH_OSD_OP_READ:
	case CEPH_OSD_OP_WRITE:
	case CEPH_OSD_OP_WRITEFULL:
		ceph_osd_data_release(&op->extent.osd_data);
		break;
	case CEPH_OSD_OP_CALL:
		ceph_osd_data_release(&op->cls.request_info);
		ceph_osd_data_release(&op->cls.request_data);
		ceph_osd_data_release(&op->cls.response_data);
		break;
	case CEPH_OSD_OP_SETXATTR:
	case CEPH_OSD_OP_CMPXATTR:
		ceph_osd_data_release(&op->xattr.osd_data);
		break;
	case CEPH_OSD_OP_STAT:
		ceph_osd_data_release(&op->raw_data_in);
		break;
	case CEPH_OSD_OP_NOTIFY_ACK:
		ceph_osd_data_release(&op->notify_ack.request_data);
		break;
	case CEPH_OSD_OP_NOTIFY:
		ceph_osd_data_release(&op->notify.request_data);
		ceph_osd_data_release(&op->notify.response_data);
		break;
	case CEPH_OSD_OP_LIST_WATCHERS:
		ceph_osd_data_release(&op->list_watchers.response_data);
		break;
	case CEPH_OSD_OP_COPY_FROM:
		ceph_osd_data_release(&op->copy_from.osd_data);
		break;
	default:
		break;
	}
}
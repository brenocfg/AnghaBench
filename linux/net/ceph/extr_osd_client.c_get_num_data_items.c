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
struct ceph_osd_request {size_t r_num_ops; struct ceph_osd_req_op* r_ops; } ;
struct ceph_osd_req_op {int op; } ;

/* Variables and functions */
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
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  osd_req_opcode_valid (int) ; 

__attribute__((used)) static void get_num_data_items(struct ceph_osd_request *req,
			       int *num_request_data_items,
			       int *num_reply_data_items)
{
	struct ceph_osd_req_op *op;

	*num_request_data_items = 0;
	*num_reply_data_items = 0;

	for (op = req->r_ops; op != &req->r_ops[req->r_num_ops]; op++) {
		switch (op->op) {
		/* request */
		case CEPH_OSD_OP_WRITE:
		case CEPH_OSD_OP_WRITEFULL:
		case CEPH_OSD_OP_SETXATTR:
		case CEPH_OSD_OP_CMPXATTR:
		case CEPH_OSD_OP_NOTIFY_ACK:
		case CEPH_OSD_OP_COPY_FROM:
			*num_request_data_items += 1;
			break;

		/* reply */
		case CEPH_OSD_OP_STAT:
		case CEPH_OSD_OP_READ:
		case CEPH_OSD_OP_LIST_WATCHERS:
			*num_reply_data_items += 1;
			break;

		/* both */
		case CEPH_OSD_OP_NOTIFY:
			*num_request_data_items += 1;
			*num_reply_data_items += 1;
			break;
		case CEPH_OSD_OP_CALL:
			*num_request_data_items += 2;
			*num_reply_data_items += 1;
			break;

		default:
			WARN_ON(!osd_req_opcode_valid(op->op));
			break;
		}
	}
}
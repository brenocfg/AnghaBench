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
struct ceph_timespec {int dummy; } ;
struct TYPE_6__ {scalar_t__ name_len; } ;
struct ceph_osd_request {int r_num_ops; struct ceph_msg* r_reply; scalar_t__ r_mempool; TYPE_3__ r_base_oid; struct ceph_msg* r_request; TYPE_1__* r_snapc; int /*<<< orphan*/  r_base_oloc; struct ceph_osd_client* r_osdc; } ;
struct ceph_osd_reqid {int dummy; } ;
struct ceph_osd_op {int dummy; } ;
struct ceph_osd_client {int /*<<< orphan*/  msgpool_op_reply; int /*<<< orphan*/  msgpool_op; } ;
struct TYPE_5__ {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct ceph_msg {TYPE_2__ front; } ;
struct ceph_blkin_trace_info {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int num_snaps; } ;

/* Variables and functions */
 int CEPH_ENCODING_START_BLK_LEN ; 
 int /*<<< orphan*/  CEPH_MSG_OSD_OP ; 
 int /*<<< orphan*/  CEPH_MSG_OSD_OPREPLY ; 
 int CEPH_PGID_ENCODING_LEN ; 
 int ENOMEM ; 
 int OSD_OPREPLY_FRONT_LEN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ceph_msg* ceph_msg_new2 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 struct ceph_msg* ceph_msgpool_get (int /*<<< orphan*/ *,int,int) ; 
 int ceph_oid_empty (TYPE_3__*) ; 
 int ceph_oloc_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ ceph_oloc_encoding_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ceph_osdc_alloc_messages(struct ceph_osd_request *req, gfp_t gfp,
				      int num_request_data_items,
				      int num_reply_data_items)
{
	struct ceph_osd_client *osdc = req->r_osdc;
	struct ceph_msg *msg;
	int msg_size;

	WARN_ON(req->r_request || req->r_reply);
	WARN_ON(ceph_oid_empty(&req->r_base_oid));
	WARN_ON(ceph_oloc_empty(&req->r_base_oloc));

	/* create request message */
	msg_size = CEPH_ENCODING_START_BLK_LEN +
			CEPH_PGID_ENCODING_LEN + 1; /* spgid */
	msg_size += 4 + 4 + 4; /* hash, osdmap_epoch, flags */
	msg_size += CEPH_ENCODING_START_BLK_LEN +
			sizeof(struct ceph_osd_reqid); /* reqid */
	msg_size += sizeof(struct ceph_blkin_trace_info); /* trace */
	msg_size += 4 + sizeof(struct ceph_timespec); /* client_inc, mtime */
	msg_size += CEPH_ENCODING_START_BLK_LEN +
			ceph_oloc_encoding_size(&req->r_base_oloc); /* oloc */
	msg_size += 4 + req->r_base_oid.name_len; /* oid */
	msg_size += 2 + req->r_num_ops * sizeof(struct ceph_osd_op);
	msg_size += 8; /* snapid */
	msg_size += 8; /* snap_seq */
	msg_size += 4 + 8 * (req->r_snapc ? req->r_snapc->num_snaps : 0);
	msg_size += 4 + 8; /* retry_attempt, features */

	if (req->r_mempool)
		msg = ceph_msgpool_get(&osdc->msgpool_op, msg_size,
				       num_request_data_items);
	else
		msg = ceph_msg_new2(CEPH_MSG_OSD_OP, msg_size,
				    num_request_data_items, gfp, true);
	if (!msg)
		return -ENOMEM;

	memset(msg->front.iov_base, 0, msg->front.iov_len);
	req->r_request = msg;

	/* create reply message */
	msg_size = OSD_OPREPLY_FRONT_LEN;
	msg_size += req->r_base_oid.name_len;
	msg_size += req->r_num_ops * sizeof(struct ceph_osd_op);

	if (req->r_mempool)
		msg = ceph_msgpool_get(&osdc->msgpool_op_reply, msg_size,
				       num_reply_data_items);
	else
		msg = ceph_msg_new2(CEPH_MSG_OSD_OPREPLY, msg_size,
				    num_reply_data_items, gfp, true);
	if (!msg)
		return -ENOMEM;

	req->r_reply = msg;

	return 0;
}
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
typedef  scalar_t__ u64 ;
struct ceph_osd_request {unsigned int r_num_ops; struct ceph_osd_req_op* r_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct ceph_osd_req_op {scalar_t__ op; int /*<<< orphan*/  indata_len; TYPE_1__ extent; int /*<<< orphan*/  outdata_len; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CEPH_OSD_OP_WRITE ; 
 scalar_t__ CEPH_OSD_OP_WRITEFULL ; 
 struct ceph_osd_req_op* _osd_req_op_init (struct ceph_osd_request*,unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 

void osd_req_op_extent_dup_last(struct ceph_osd_request *osd_req,
				unsigned int which, u64 offset_inc)
{
	struct ceph_osd_req_op *op, *prev_op;

	BUG_ON(which + 1 >= osd_req->r_num_ops);

	prev_op = &osd_req->r_ops[which];
	op = _osd_req_op_init(osd_req, which + 1, prev_op->op, prev_op->flags);
	/* dup previous one */
	op->indata_len = prev_op->indata_len;
	op->outdata_len = prev_op->outdata_len;
	op->extent = prev_op->extent;
	/* adjust offset */
	op->extent.offset += offset_inc;
	op->extent.length -= offset_inc;

	if (op->op == CEPH_OSD_OP_WRITE || op->op == CEPH_OSD_OP_WRITEFULL)
		op->indata_len -= offset_inc;
}
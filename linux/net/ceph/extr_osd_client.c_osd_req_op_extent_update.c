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
struct TYPE_2__ {scalar_t__ length; } ;
struct ceph_osd_req_op {scalar_t__ op; int /*<<< orphan*/  indata_len; TYPE_1__ extent; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CEPH_OSD_OP_WRITE ; 
 scalar_t__ CEPH_OSD_OP_WRITEFULL ; 

void osd_req_op_extent_update(struct ceph_osd_request *osd_req,
				unsigned int which, u64 length)
{
	struct ceph_osd_req_op *op;
	u64 previous;

	BUG_ON(which >= osd_req->r_num_ops);
	op = &osd_req->r_ops[which];
	previous = op->extent.length;

	if (length == previous)
		return;		/* Nothing to do */
	BUG_ON(length > previous);

	op->extent.length = length;
	if (op->op == CEPH_OSD_OP_WRITE || op->op == CEPH_OSD_OP_WRITEFULL)
		op->indata_len -= previous - length;
}
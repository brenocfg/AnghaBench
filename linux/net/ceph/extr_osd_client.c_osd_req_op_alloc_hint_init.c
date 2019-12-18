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
typedef  void* u64 ;
struct ceph_osd_request {int dummy; } ;
struct TYPE_2__ {void* expected_write_size; void* expected_object_size; } ;
struct ceph_osd_req_op {int /*<<< orphan*/  flags; TYPE_1__ alloc_hint; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_OP_FLAG_FAILOK ; 
 int /*<<< orphan*/  CEPH_OSD_OP_SETALLOCHINT ; 
 struct ceph_osd_req_op* _osd_req_op_init (struct ceph_osd_request*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void osd_req_op_alloc_hint_init(struct ceph_osd_request *osd_req,
				unsigned int which,
				u64 expected_object_size,
				u64 expected_write_size)
{
	struct ceph_osd_req_op *op = _osd_req_op_init(osd_req, which,
						      CEPH_OSD_OP_SETALLOCHINT,
						      0);

	op->alloc_hint.expected_object_size = expected_object_size;
	op->alloc_hint.expected_write_size = expected_write_size;

	/*
	 * CEPH_OSD_OP_SETALLOCHINT op is advisory and therefore deemed
	 * not worth a feature bit.  Set FAILOK per-op flag to make
	 * sure older osds don't trip over an unsupported opcode.
	 */
	op->flags |= CEPH_OSD_OP_FLAG_FAILOK;
}
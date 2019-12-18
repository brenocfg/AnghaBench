#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;
struct ceph_osd_request {TYPE_2__* r_ops; } ;
struct ceph_osd_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  indata_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  indata_len; TYPE_1__ cls; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_osd_data_pages_init (struct ceph_osd_data*,struct page**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cls ; 
 struct ceph_osd_data* osd_req_op_data (struct ceph_osd_request*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_data ; 

void osd_req_op_cls_request_data_pages(struct ceph_osd_request *osd_req,
			unsigned int which, struct page **pages, u64 length,
			u32 alignment, bool pages_from_pool, bool own_pages)
{
	struct ceph_osd_data *osd_data;

	osd_data = osd_req_op_data(osd_req, which, cls, request_data);
	ceph_osd_data_pages_init(osd_data, pages, length, alignment,
				pages_from_pool, own_pages);
	osd_req->r_ops[which].cls.indata_len += length;
	osd_req->r_ops[which].indata_len += length;
}
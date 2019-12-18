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
struct ceph_pagelist {int dummy; } ;
struct ceph_osd_request {int dummy; } ;
struct TYPE_2__ {char const* class_name; size_t class_len; char const* method_name; size_t method_len; } ;
struct ceph_osd_req_op {size_t indata_len; TYPE_1__ cls; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CEPH_OSD_OP_CALL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ U8_MAX ; 
 struct ceph_osd_req_op* _osd_req_op_init (struct ceph_osd_request*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ceph_pagelist* ceph_pagelist_alloc (int /*<<< orphan*/ ) ; 
 int ceph_pagelist_append (struct ceph_pagelist*,char const*,size_t) ; 
 int /*<<< orphan*/  ceph_pagelist_release (struct ceph_pagelist*) ; 
 int /*<<< orphan*/  osd_req_op_cls_request_info_pagelist (struct ceph_osd_request*,unsigned int,struct ceph_pagelist*) ; 
 size_t strlen (char const*) ; 

int osd_req_op_cls_init(struct ceph_osd_request *osd_req, unsigned int which,
			const char *class, const char *method)
{
	struct ceph_osd_req_op *op;
	struct ceph_pagelist *pagelist;
	size_t payload_len = 0;
	size_t size;
	int ret;

	op = _osd_req_op_init(osd_req, which, CEPH_OSD_OP_CALL, 0);

	pagelist = ceph_pagelist_alloc(GFP_NOFS);
	if (!pagelist)
		return -ENOMEM;

	op->cls.class_name = class;
	size = strlen(class);
	BUG_ON(size > (size_t) U8_MAX);
	op->cls.class_len = size;
	ret = ceph_pagelist_append(pagelist, class, size);
	if (ret)
		goto err_pagelist_free;
	payload_len += size;

	op->cls.method_name = method;
	size = strlen(method);
	BUG_ON(size > (size_t) U8_MAX);
	op->cls.method_len = size;
	ret = ceph_pagelist_append(pagelist, method, size);
	if (ret)
		goto err_pagelist_free;
	payload_len += size;

	osd_req_op_cls_request_info_pagelist(osd_req, which, pagelist);
	op->indata_len = payload_len;
	return 0;

err_pagelist_free:
	ceph_pagelist_release(pagelist);
	return ret;
}
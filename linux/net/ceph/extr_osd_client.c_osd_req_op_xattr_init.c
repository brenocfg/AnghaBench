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
typedef  void* u8 ;
typedef  scalar_t__ u16 ;
struct ceph_pagelist {int dummy; } ;
struct ceph_osd_request {int dummy; } ;
struct TYPE_2__ {size_t name_len; size_t value_len; int /*<<< orphan*/  osd_data; void* cmp_mode; void* cmp_op; } ;
struct ceph_osd_req_op {size_t indata_len; TYPE_1__ xattr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CEPH_OSD_OP_CMPXATTR ; 
 scalar_t__ CEPH_OSD_OP_SETXATTR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct ceph_osd_req_op* _osd_req_op_init (struct ceph_osd_request*,unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_osd_data_pagelist_init (int /*<<< orphan*/ *,struct ceph_pagelist*) ; 
 struct ceph_pagelist* ceph_pagelist_alloc (int /*<<< orphan*/ ) ; 
 int ceph_pagelist_append (struct ceph_pagelist*,void const*,size_t) ; 
 int /*<<< orphan*/  ceph_pagelist_release (struct ceph_pagelist*) ; 
 size_t strlen (char const*) ; 

int osd_req_op_xattr_init(struct ceph_osd_request *osd_req, unsigned int which,
			  u16 opcode, const char *name, const void *value,
			  size_t size, u8 cmp_op, u8 cmp_mode)
{
	struct ceph_osd_req_op *op = _osd_req_op_init(osd_req, which,
						      opcode, 0);
	struct ceph_pagelist *pagelist;
	size_t payload_len;
	int ret;

	BUG_ON(opcode != CEPH_OSD_OP_SETXATTR && opcode != CEPH_OSD_OP_CMPXATTR);

	pagelist = ceph_pagelist_alloc(GFP_NOFS);
	if (!pagelist)
		return -ENOMEM;

	payload_len = strlen(name);
	op->xattr.name_len = payload_len;
	ret = ceph_pagelist_append(pagelist, name, payload_len);
	if (ret)
		goto err_pagelist_free;

	op->xattr.value_len = size;
	ret = ceph_pagelist_append(pagelist, value, size);
	if (ret)
		goto err_pagelist_free;
	payload_len += size;

	op->xattr.cmp_op = cmp_op;
	op->xattr.cmp_mode = cmp_mode;

	ceph_osd_data_pagelist_init(&op->xattr.osd_data, pagelist);
	op->indata_len = payload_len;
	return 0;

err_pagelist_free:
	ceph_pagelist_release(pagelist);
	return ret;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  iov_base; } ;
struct ceph_buffer {TYPE_1__ vec; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  bad ; 
 struct ceph_buffer* ceph_buffer_new (size_t,int /*<<< orphan*/ ) ; 
 size_t ceph_decode_32 (void**) ; 
 int /*<<< orphan*/  ceph_decode_copy (void**,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,int) ; 

int ceph_decode_buffer(struct ceph_buffer **b, void **p, void *end)
{
	size_t len;

	ceph_decode_need(p, end, sizeof(u32), bad);
	len = ceph_decode_32(p);
	dout("decode_buffer len %d\n", (int)len);
	ceph_decode_need(p, end, len, bad);
	*b = ceph_buffer_new(len, GFP_NOFS);
	if (!*b)
		return -ENOMEM;
	ceph_decode_copy(p, (*b)->vec.iov_base, len);
	return 0;
bad:
	return -EINVAL;
}
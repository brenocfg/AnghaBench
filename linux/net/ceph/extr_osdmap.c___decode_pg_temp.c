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
typedef  int u32 ;
struct TYPE_2__ {int len; int /*<<< orphan*/ * osds; } ;
struct ceph_pg_mapping {TYPE_1__ pg_temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct ceph_pg_mapping* ERR_PTR (int /*<<< orphan*/ ) ; 
 int SIZE_MAX ; 
 struct ceph_pg_mapping* alloc_pg_mapping (int) ; 
 int /*<<< orphan*/  ceph_decode_32 (void**) ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_inval ; 

__attribute__((used)) static struct ceph_pg_mapping *__decode_pg_temp(void **p, void *end,
						bool incremental)
{
	struct ceph_pg_mapping *pg;
	u32 len, i;

	ceph_decode_32_safe(p, end, len, e_inval);
	if (len == 0 && incremental)
		return NULL;	/* new_pg_temp: [] to remove */
	if (len > (SIZE_MAX - sizeof(*pg)) / sizeof(u32))
		return ERR_PTR(-EINVAL);

	ceph_decode_need(p, end, len * sizeof(u32), e_inval);
	pg = alloc_pg_mapping(len * sizeof(u32));
	if (!pg)
		return ERR_PTR(-ENOMEM);

	pg->pg_temp.len = len;
	for (i = 0; i < len; i++)
		pg->pg_temp.osds[i] = ceph_decode_32(p);

	return pg;

e_inval:
	return ERR_PTR(-EINVAL);
}
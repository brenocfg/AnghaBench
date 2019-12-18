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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ osd; } ;
struct ceph_pg_mapping {TYPE_1__ primary_temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct ceph_pg_mapping* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct ceph_pg_mapping* alloc_pg_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_inval ; 

__attribute__((used)) static struct ceph_pg_mapping *__decode_primary_temp(void **p, void *end,
						     bool incremental)
{
	struct ceph_pg_mapping *pg;
	u32 osd;

	ceph_decode_32_safe(p, end, osd, e_inval);
	if (osd == (u32)-1 && incremental)
		return NULL;	/* new_primary_temp: -1 to remove */

	pg = alloc_pg_mapping(0);
	if (!pg)
		return ERR_PTR(-ENOMEM);

	pg->primary_temp.osd = osd;
	return pg;

e_inval:
	return ERR_PTR(-EINVAL);
}
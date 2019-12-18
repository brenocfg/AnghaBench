#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ceph_osdmap {scalar_t__ max_osd; int /*<<< orphan*/ * osd_primary_affinity; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ceph_decode_32 (void**) ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_inval ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int set_primary_affinity (struct ceph_osdmap*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_primary_affinity(void **p, void *end,
				   struct ceph_osdmap *map)
{
	u32 len, i;

	ceph_decode_32_safe(p, end, len, e_inval);
	if (len == 0) {
		kvfree(map->osd_primary_affinity);
		map->osd_primary_affinity = NULL;
		return 0;
	}
	if (len != map->max_osd)
		goto e_inval;

	ceph_decode_need(p, end, map->max_osd*sizeof(u32), e_inval);

	for (i = 0; i < map->max_osd; i++) {
		int ret;

		ret = set_primary_affinity(map, i, ceph_decode_32(p));
		if (ret)
			return ret;
	}

	return 0;

e_inval:
	return -EINVAL;
}
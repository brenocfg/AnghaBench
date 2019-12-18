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
typedef  int u8 ;
typedef  int u32 ;
struct ceph_osdmap {size_t max_osd; int* osd_weight; int* osd_state; struct ceph_entity_addr* osd_addr; } ;
struct ceph_entity_addr {int dummy; } ;
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CEPH_OSD_AUTOOUT ; 
 int /*<<< orphan*/  CEPH_OSD_DEFAULT_PRIMARY_AFFINITY ; 
 int CEPH_OSD_EXISTS ; 
 int CEPH_OSD_IN ; 
 int CEPH_OSD_NEW ; 
 int CEPH_OSD_OUT ; 
 int CEPH_OSD_UP ; 
 int EINVAL ; 
 void* ceph_decode_32 (void**) ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,int,int /*<<< orphan*/ ) ; 
 int ceph_decode_8 (void**) ; 
 scalar_t__ ceph_decode_entity_addr (void**,void*,struct ceph_entity_addr*) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_skip_32 (void**,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_inval ; 
 int /*<<< orphan*/  memset (struct ceph_entity_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,size_t,...) ; 
 int set_primary_affinity (struct ceph_osdmap*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_new_up_state_weight(void **p, void *end, u8 struct_v,
				      struct ceph_osdmap *map)
{
	void *new_up_client;
	void *new_state;
	void *new_weight_end;
	u32 len;
	int i;

	new_up_client = *p;
	ceph_decode_32_safe(p, end, len, e_inval);
	for (i = 0; i < len; ++i) {
		struct ceph_entity_addr addr;

		ceph_decode_skip_32(p, end, e_inval);
		if (ceph_decode_entity_addr(p, end, &addr))
			goto e_inval;
	}

	new_state = *p;
	ceph_decode_32_safe(p, end, len, e_inval);
	len *= sizeof(u32) + (struct_v >= 5 ? sizeof(u32) : sizeof(u8));
	ceph_decode_need(p, end, len, e_inval);
	*p += len;

	/* new_weight */
	ceph_decode_32_safe(p, end, len, e_inval);
	while (len--) {
		s32 osd;
		u32 w;

		ceph_decode_need(p, end, 2*sizeof(u32), e_inval);
		osd = ceph_decode_32(p);
		w = ceph_decode_32(p);
		BUG_ON(osd >= map->max_osd);
		pr_info("osd%d weight 0x%x %s\n", osd, w,
		     w == CEPH_OSD_IN ? "(in)" :
		     (w == CEPH_OSD_OUT ? "(out)" : ""));
		map->osd_weight[osd] = w;

		/*
		 * If we are marking in, set the EXISTS, and clear the
		 * AUTOOUT and NEW bits.
		 */
		if (w) {
			map->osd_state[osd] |= CEPH_OSD_EXISTS;
			map->osd_state[osd] &= ~(CEPH_OSD_AUTOOUT |
						 CEPH_OSD_NEW);
		}
	}
	new_weight_end = *p;

	/* new_state (up/down) */
	*p = new_state;
	len = ceph_decode_32(p);
	while (len--) {
		s32 osd;
		u32 xorstate;
		int ret;

		osd = ceph_decode_32(p);
		if (struct_v >= 5)
			xorstate = ceph_decode_32(p);
		else
			xorstate = ceph_decode_8(p);
		if (xorstate == 0)
			xorstate = CEPH_OSD_UP;
		BUG_ON(osd >= map->max_osd);
		if ((map->osd_state[osd] & CEPH_OSD_UP) &&
		    (xorstate & CEPH_OSD_UP))
			pr_info("osd%d down\n", osd);
		if ((map->osd_state[osd] & CEPH_OSD_EXISTS) &&
		    (xorstate & CEPH_OSD_EXISTS)) {
			pr_info("osd%d does not exist\n", osd);
			ret = set_primary_affinity(map, osd,
						   CEPH_OSD_DEFAULT_PRIMARY_AFFINITY);
			if (ret)
				return ret;
			memset(map->osd_addr + osd, 0, sizeof(*map->osd_addr));
			map->osd_state[osd] = 0;
		} else {
			map->osd_state[osd] ^= xorstate;
		}
	}

	/* new_up_client */
	*p = new_up_client;
	len = ceph_decode_32(p);
	while (len--) {
		s32 osd;
		struct ceph_entity_addr addr;

		osd = ceph_decode_32(p);
		BUG_ON(osd >= map->max_osd);
		if (ceph_decode_entity_addr(p, end, &addr))
			goto e_inval;
		pr_info("osd%d up\n", osd);
		map->osd_state[osd] |= CEPH_OSD_EXISTS | CEPH_OSD_UP;
		map->osd_addr[osd] = addr;
	}

	*p = new_weight_end;
	return 0;

e_inval:
	return -EINVAL;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct ceph_osdmap {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_inval ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_primary_affinity (struct ceph_osdmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_new_primary_affinity(void **p, void *end,
				       struct ceph_osdmap *map)
{
	u32 n;

	ceph_decode_32_safe(p, end, n, e_inval);
	while (n--) {
		u32 osd, aff;
		int ret;

		ceph_decode_32_safe(p, end, osd, e_inval);
		ceph_decode_32_safe(p, end, aff, e_inval);

		ret = set_primary_affinity(map, osd, aff);
		if (ret)
			return ret;

		pr_info("osd%d primary-affinity 0x%x\n", osd, aff);
	}

	return 0;

e_inval:
	return -EINVAL;
}
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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct ceph_mds_reply_lease {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  bad ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_8_safe (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_reply_info_lease(void **p, void *end,
				  struct ceph_mds_reply_lease **lease,
				  u64 features)
{
	if (features == (u64)-1) {
		u8 struct_v, struct_compat;
		u32 struct_len;
		ceph_decode_8_safe(p, end, struct_v, bad);
		ceph_decode_8_safe(p, end, struct_compat, bad);
		/* struct_v is expected to be >= 1. we only understand
		 * encoding whose struct_compat == 1. */
		if (!struct_v || struct_compat != 1)
			goto bad;
		ceph_decode_32_safe(p, end, struct_len, bad);
		ceph_decode_need(p, end, struct_len, bad);
		end = *p + struct_len;
	}

	ceph_decode_need(p, end, sizeof(**lease), bad);
	*lease = *p;
	*p += sizeof(**lease);
	if (features == (u64)-1)
		*p = end;
	return 0;
bad:
	return -EIO;
}
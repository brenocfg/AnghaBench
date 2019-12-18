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

/* Variables and functions */
 int /*<<< orphan*/  bad ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (void*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strnstr (void*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __decode_session_metadata(void **p, void *end,
				     bool *blacklisted)
{
	/* map<string,string> */
	u32 n;
	bool err_str;
	ceph_decode_32_safe(p, end, n, bad);
	while (n-- > 0) {
		u32 len;
		ceph_decode_32_safe(p, end, len, bad);
		ceph_decode_need(p, end, len, bad);
		err_str = !strncmp(*p, "error_string", len);
		*p += len;
		ceph_decode_32_safe(p, end, len, bad);
		ceph_decode_need(p, end, len, bad);
		if (err_str && strnstr(*p, "blacklisted", len))
			*blacklisted = true;
		*p += len;
	}
	return 0;
bad:
	return -1;
}
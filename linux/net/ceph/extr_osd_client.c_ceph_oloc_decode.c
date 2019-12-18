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
struct ceph_object_locator {scalar_t__ pool_ns; void* pool; } ;
typedef  int s64 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ceph_compare_string (scalar_t__,void*,int) ; 
 int ceph_decode_32 (void**) ; 
 void* ceph_decode_64 (void**) ; 
 int ceph_decode_8 (void**) ; 
 int /*<<< orphan*/  ceph_decode_need (void**,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_inval ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 

__attribute__((used)) static int ceph_oloc_decode(void **p, void *end,
			    struct ceph_object_locator *oloc)
{
	u8 struct_v, struct_cv;
	u32 len;
	void *struct_end;
	int ret = 0;

	ceph_decode_need(p, end, 1 + 1 + 4, e_inval);
	struct_v = ceph_decode_8(p);
	struct_cv = ceph_decode_8(p);
	if (struct_v < 3) {
		pr_warn("got v %d < 3 cv %d of ceph_object_locator\n",
			struct_v, struct_cv);
		goto e_inval;
	}
	if (struct_cv > 6) {
		pr_warn("got v %d cv %d > 6 of ceph_object_locator\n",
			struct_v, struct_cv);
		goto e_inval;
	}
	len = ceph_decode_32(p);
	ceph_decode_need(p, end, len, e_inval);
	struct_end = *p + len;

	oloc->pool = ceph_decode_64(p);
	*p += 4; /* skip preferred */

	len = ceph_decode_32(p);
	if (len > 0) {
		pr_warn("ceph_object_locator::key is set\n");
		goto e_inval;
	}

	if (struct_v >= 5) {
		bool changed = false;

		len = ceph_decode_32(p);
		if (len > 0) {
			ceph_decode_need(p, end, len, e_inval);
			if (!oloc->pool_ns ||
			    ceph_compare_string(oloc->pool_ns, *p, len))
				changed = true;
			*p += len;
		} else {
			if (oloc->pool_ns)
				changed = true;
		}
		if (changed) {
			/* redirect changes namespace */
			pr_warn("ceph_object_locator::nspace is changed\n");
			goto e_inval;
		}
	}

	if (struct_v >= 6) {
		s64 hash = ceph_decode_64(p);
		if (hash != -1) {
			pr_warn("ceph_object_locator::hash is set\n");
			goto e_inval;
		}
	}

	/* skip the rest */
	*p = struct_end;
out:
	return ret;

e_inval:
	ret = -EINVAL;
	goto out;
}
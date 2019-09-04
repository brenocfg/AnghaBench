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
struct rb_root {int dummy; } ;
struct ceph_pg {int dummy; } ;
struct ceph_pg_mapping {struct ceph_pg pgid; } ;
typedef  struct ceph_pg_mapping* (* decode_mapping_fn_t ) (void**,void*,int) ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct ceph_pg_mapping*) ; 
 int PTR_ERR (struct ceph_pg_mapping*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ceph_decode_32_safe (void**,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ceph_decode_pgid (void**,void*,struct ceph_pg*) ; 
 int /*<<< orphan*/  e_inval ; 
 int /*<<< orphan*/  erase_pg_mapping (struct rb_root*,struct ceph_pg_mapping*) ; 
 int /*<<< orphan*/  free_pg_mapping (struct ceph_pg_mapping*) ; 
 int /*<<< orphan*/  insert_pg_mapping (struct rb_root*,struct ceph_pg_mapping*) ; 
 struct ceph_pg_mapping* lookup_pg_mapping (struct rb_root*,struct ceph_pg*) ; 

__attribute__((used)) static int decode_pg_mapping(void **p, void *end, struct rb_root *mapping_root,
			     decode_mapping_fn_t fn, bool incremental)
{
	u32 n;

	WARN_ON(!incremental && !fn);

	ceph_decode_32_safe(p, end, n, e_inval);
	while (n--) {
		struct ceph_pg_mapping *pg;
		struct ceph_pg pgid;
		int ret;

		ret = ceph_decode_pgid(p, end, &pgid);
		if (ret)
			return ret;

		pg = lookup_pg_mapping(mapping_root, &pgid);
		if (pg) {
			WARN_ON(!incremental);
			erase_pg_mapping(mapping_root, pg);
			free_pg_mapping(pg);
		}

		if (fn) {
			pg = fn(p, end, incremental);
			if (IS_ERR(pg))
				return PTR_ERR(pg);

			if (pg) {
				pg->pgid = pgid; /* struct */
				insert_pg_mapping(mapping_root, pg);
			}
		}
	}

	return 0;

e_inval:
	return -EINVAL;
}
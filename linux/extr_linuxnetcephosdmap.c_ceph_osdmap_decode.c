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
struct ceph_osdmap {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ceph_osdmap* ERR_PTR (int) ; 
 struct ceph_osdmap* ceph_osdmap_alloc () ; 
 int /*<<< orphan*/  ceph_osdmap_destroy (struct ceph_osdmap*) ; 
 int osdmap_decode (void**,void*,struct ceph_osdmap*) ; 

struct ceph_osdmap *ceph_osdmap_decode(void **p, void *end)
{
	struct ceph_osdmap *map;
	int ret;

	map = ceph_osdmap_alloc();
	if (!map)
		return ERR_PTR(-ENOMEM);

	ret = osdmap_decode(p, end, map);
	if (ret) {
		ceph_osdmap_destroy(map);
		return ERR_PTR(ret);
	}

	return map;
}
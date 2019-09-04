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
struct ceph_pagelist {size_t room; int length; scalar_t__ mapped_tail; } ;

/* Variables and functions */
 int PAGE_MASK ; 
 int ceph_pagelist_addpage (struct ceph_pagelist*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 

int ceph_pagelist_append(struct ceph_pagelist *pl, const void *buf, size_t len)
{
	while (pl->room < len) {
		size_t bit = pl->room;
		int ret;

		memcpy(pl->mapped_tail + (pl->length & ~PAGE_MASK),
		       buf, bit);
		pl->length += bit;
		pl->room -= bit;
		buf += bit;
		len -= bit;
		ret = ceph_pagelist_addpage(pl);
		if (ret)
			return ret;
	}

	memcpy(pl->mapped_tail + (pl->length & ~PAGE_MASK), buf, len);
	pl->length += len;
	pl->room -= len;
	return 0;
}
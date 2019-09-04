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
 int __decode_pools (void**,void*,struct ceph_osdmap*,int) ; 

__attribute__((used)) static int decode_new_pools(void **p, void *end, struct ceph_osdmap *map)
{
	return __decode_pools(p, end, map, true);
}
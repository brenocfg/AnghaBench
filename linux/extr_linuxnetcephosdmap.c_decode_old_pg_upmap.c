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
struct ceph_osdmap {int /*<<< orphan*/  pg_upmap; } ;

/* Variables and functions */
 int decode_pg_mapping (void**,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_old_pg_upmap(void **p, void *end, struct ceph_osdmap *map)
{
	return decode_pg_mapping(p, end, &map->pg_upmap, NULL, true);
}
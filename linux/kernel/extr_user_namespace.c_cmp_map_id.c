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
typedef  scalar_t__ u32 ;
struct uid_gid_extent {scalar_t__ lower_first; scalar_t__ first; scalar_t__ count; } ;
struct idmap_key {scalar_t__ id; scalar_t__ count; scalar_t__ map_up; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_map_id(const void *k, const void *e)
{
	u32 first, last, id2;
	const struct idmap_key *key = k;
	const struct uid_gid_extent *el = e;

	id2 = key->id + key->count - 1;

	/* handle map_id_{down,up}() */
	if (key->map_up)
		first = el->lower_first;
	else
		first = el->first;

	last = first + el->count - 1;

	if (key->id >= first && key->id <= last &&
	    (id2 >= first && id2 <= last))
		return 0;

	if (key->id < first || id2 < first)
		return -1;

	return 1;
}
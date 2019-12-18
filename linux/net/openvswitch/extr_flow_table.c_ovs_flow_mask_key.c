#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int start; } ;
struct sw_flow_mask {int /*<<< orphan*/  key; TYPE_1__ range; } ;
struct sw_flow_key {int dummy; } ;

/* Variables and functions */
 int range_n_bytes (TYPE_1__*) ; 

void ovs_flow_mask_key(struct sw_flow_key *dst, const struct sw_flow_key *src,
		       bool full, const struct sw_flow_mask *mask)
{
	int start = full ? 0 : mask->range.start;
	int len = full ? sizeof *dst : range_n_bytes(&mask->range);
	const long *m = (const long *)((const u8 *)&mask->key + start);
	const long *s = (const long *)((const u8 *)src + start);
	long *d = (long *)((u8 *)dst + start);
	int i;

	/* If 'full' is true then all of 'dst' is fully initialized. Otherwise,
	 * if 'full' is false the memory outside of the 'mask->range' is left
	 * uninitialized. This can be used as an optimization when further
	 * operations on 'dst' only use contents within 'mask->range'.
	 */
	for (i = 0; i < len; i += sizeof(long))
		*d++ = *s++ & *m++;
}
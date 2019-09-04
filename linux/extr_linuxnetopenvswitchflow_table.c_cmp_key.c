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
typedef  int /*<<< orphan*/  u8 ;
struct sw_flow_key {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool cmp_key(const struct sw_flow_key *key1,
		    const struct sw_flow_key *key2,
		    int key_start, int key_end)
{
	const long *cp1 = (const long *)((const u8 *)key1 + key_start);
	const long *cp2 = (const long *)((const u8 *)key2 + key_start);
	long diffs = 0;
	int i;

	for (i = key_start; i < key_end;  i += sizeof(long))
		diffs |= *cp1++ ^ *cp2++;

	return diffs == 0;
}
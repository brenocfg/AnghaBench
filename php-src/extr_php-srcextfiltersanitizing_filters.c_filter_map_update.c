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
typedef  int* filter_map ;

/* Variables and functions */
 size_t strlen (char const*) ; 

__attribute__((used)) static void filter_map_update(filter_map *map, int flag, const unsigned char *allowed_list)
{
	size_t l, i;

	l = strlen((const char*)allowed_list);
	for (i = 0; i < l; ++i) {
		(*map)[allowed_list[i]] = flag;
	}
}
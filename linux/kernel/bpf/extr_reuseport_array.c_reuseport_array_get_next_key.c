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
typedef  int u32 ;
struct TYPE_2__ {int max_entries; } ;
struct reuseport_array {TYPE_1__ map; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int U32_MAX ; 
 struct reuseport_array* reuseport_array (struct bpf_map*) ; 

__attribute__((used)) static int reuseport_array_get_next_key(struct bpf_map *map, void *key,
					void *next_key)
{
	struct reuseport_array *array = reuseport_array(map);
	u32 index = key ? *(u32 *)key : U32_MAX;
	u32 *next = (u32 *)next_key;

	if (index >= array->map.max_entries) {
		*next = 0;
		return 0;
	}

	if (index == array->map.max_entries - 1)
		return -ENOENT;

	*next = index + 1;
	return 0;
}
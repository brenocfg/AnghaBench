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
struct htab_elem {int dummy; } ;
struct bpf_map {int /*<<< orphan*/  key_size; } ;

/* Variables and functions */
 struct htab_elem* __htab_map_lookup_elem (struct bpf_map*,void*) ; 
 int /*<<< orphan*/  htab_elem_get_ptr (struct htab_elem*,int /*<<< orphan*/ ) ; 
 void* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *htab_percpu_map_lookup_elem(struct bpf_map *map, void *key)
{
	struct htab_elem *l = __htab_map_lookup_elem(map, key);

	if (l)
		return this_cpu_ptr(htab_elem_get_ptr(l, map->key_size));
	else
		return NULL;
}
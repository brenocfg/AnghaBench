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
union bpf_attr {int /*<<< orphan*/  inner_map_fd; } ;
struct bpf_map {struct bpf_map* inner_map_meta; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct bpf_map*) ; 
 struct bpf_map* array_map_alloc (union bpf_attr*) ; 
 struct bpf_map* bpf_map_meta_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_map_meta_free (struct bpf_map*) ; 

__attribute__((used)) static struct bpf_map *array_of_map_alloc(union bpf_attr *attr)
{
	struct bpf_map *map, *inner_map_meta;

	inner_map_meta = bpf_map_meta_alloc(attr->inner_map_fd);
	if (IS_ERR(inner_map_meta))
		return inner_map_meta;

	map = array_map_alloc(attr);
	if (IS_ERR(map)) {
		bpf_map_meta_free(inner_map_meta);
		return map;
	}

	map->inner_map_meta = inner_map_meta;

	return map;
}
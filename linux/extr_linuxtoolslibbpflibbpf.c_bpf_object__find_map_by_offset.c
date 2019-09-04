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
struct bpf_object {int nr_maps; struct bpf_map* maps; } ;
struct bpf_map {size_t offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct bpf_map* ERR_PTR (int /*<<< orphan*/ ) ; 

struct bpf_map *
bpf_object__find_map_by_offset(struct bpf_object *obj, size_t offset)
{
	int i;

	for (i = 0; i < obj->nr_maps; i++) {
		if (obj->maps[i].offset == offset)
			return &obj->maps[i];
	}
	return ERR_PTR(-ENOENT);
}
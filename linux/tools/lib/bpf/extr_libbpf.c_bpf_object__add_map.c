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
struct bpf_object {int nr_maps; int maps_cap; struct bpf_map* maps; } ;
struct bpf_map {int fd; int inner_map_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct bpf_map* ERR_PTR (int /*<<< orphan*/ ) ; 
 size_t max (size_t,int) ; 
 int /*<<< orphan*/  memset (struct bpf_map*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 struct bpf_map* realloc (struct bpf_map*,size_t) ; 

__attribute__((used)) static struct bpf_map *bpf_object__add_map(struct bpf_object *obj)
{
	struct bpf_map *new_maps;
	size_t new_cap;
	int i;

	if (obj->nr_maps < obj->maps_cap)
		return &obj->maps[obj->nr_maps++];

	new_cap = max((size_t)4, obj->maps_cap * 3 / 2);
	new_maps = realloc(obj->maps, new_cap * sizeof(*obj->maps));
	if (!new_maps) {
		pr_warning("alloc maps for object failed\n");
		return ERR_PTR(-ENOMEM);
	}

	obj->maps_cap = new_cap;
	obj->maps = new_maps;

	/* zero out new maps */
	memset(obj->maps + obj->nr_maps, 0,
	       (obj->maps_cap - obj->nr_maps) * sizeof(*obj->maps));
	/*
	 * fill all fd with -1 so won't close incorrect fd (fd=0 is stdin)
	 * when failure (zclose won't close negative fd)).
	 */
	for (i = obj->nr_maps; i < obj->maps_cap; i++) {
		obj->maps[i].fd = -1;
		obj->maps[i].inner_map_fd = -1;
	}

	return &obj->maps[obj->nr_maps++];
}
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
struct map_iter {void* key; } ;
struct bpf_map {int key_size; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int __GFP_NOWARN ; 
 void* kzalloc (int,int) ; 
 int /*<<< orphan*/  map_iter_free (struct map_iter*) ; 

__attribute__((used)) static struct map_iter *map_iter_alloc(struct bpf_map *map)
{
	struct map_iter *iter;

	iter = kzalloc(sizeof(*iter), GFP_KERNEL | __GFP_NOWARN);
	if (!iter)
		goto error;

	iter->key = kzalloc(map->key_size, GFP_KERNEL | __GFP_NOWARN);
	if (!iter->key)
		goto error;

	return iter;

error:
	map_iter_free(iter);
	return NULL;
}
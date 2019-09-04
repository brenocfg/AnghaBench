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
struct tracing_map_ops {int dummy; } ;
struct tracing_map_entry {int dummy; } ;
struct tracing_map {unsigned int map_bits; int max_elts; int map_size; unsigned int key_size; int* key_idx; int /*<<< orphan*/  map; void* private_data; struct tracing_map_ops const* ops; int /*<<< orphan*/  next_elt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct tracing_map* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int TRACING_MAP_BITS_MAX ; 
 unsigned int TRACING_MAP_BITS_MIN ; 
 unsigned int TRACING_MAP_KEYS_MAX ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct tracing_map* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracing_map_array_alloc (int,int) ; 
 int /*<<< orphan*/  tracing_map_destroy (struct tracing_map*) ; 

struct tracing_map *tracing_map_create(unsigned int map_bits,
				       unsigned int key_size,
				       const struct tracing_map_ops *ops,
				       void *private_data)
{
	struct tracing_map *map;
	unsigned int i;

	if (map_bits < TRACING_MAP_BITS_MIN ||
	    map_bits > TRACING_MAP_BITS_MAX)
		return ERR_PTR(-EINVAL);

	map = kzalloc(sizeof(*map), GFP_KERNEL);
	if (!map)
		return ERR_PTR(-ENOMEM);

	map->map_bits = map_bits;
	map->max_elts = (1 << map_bits);
	atomic_set(&map->next_elt, -1);

	map->map_size = (1 << (map_bits + 1));
	map->ops = ops;

	map->private_data = private_data;

	map->map = tracing_map_array_alloc(map->map_size,
					   sizeof(struct tracing_map_entry));
	if (!map->map)
		goto free;

	map->key_size = key_size;
	for (i = 0; i < TRACING_MAP_KEYS_MAX; i++)
		map->key_idx[i] = -1;
 out:
	return map;
 free:
	tracing_map_destroy(map);
	map = ERR_PTR(-ENOMEM);

	goto out;
}
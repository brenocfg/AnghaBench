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
union bpf_attr {scalar_t__ max_entries; } ;
typedef  int u64 ;
struct sock {int dummy; } ;
struct bpf_map {int /*<<< orphan*/  memory; } ;
struct reuseport_array {struct bpf_map map; } ;
struct bpf_map_memory {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENOMEM ; 
 int EPERM ; 
 struct bpf_map* ERR_PTR (int) ; 
 struct reuseport_array* bpf_map_area_alloc (int,int) ; 
 int bpf_map_attr_numa_node (union bpf_attr*) ; 
 int /*<<< orphan*/  bpf_map_charge_finish (struct bpf_map_memory*) ; 
 int bpf_map_charge_init (struct bpf_map_memory*,int) ; 
 int /*<<< orphan*/  bpf_map_charge_move (int /*<<< orphan*/ *,struct bpf_map_memory*) ; 
 int /*<<< orphan*/  bpf_map_init_from_attr (struct bpf_map*,union bpf_attr*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bpf_map *reuseport_array_alloc(union bpf_attr *attr)
{
	int err, numa_node = bpf_map_attr_numa_node(attr);
	struct reuseport_array *array;
	struct bpf_map_memory mem;
	u64 array_size;

	if (!capable(CAP_SYS_ADMIN))
		return ERR_PTR(-EPERM);

	array_size = sizeof(*array);
	array_size += (u64)attr->max_entries * sizeof(struct sock *);

	err = bpf_map_charge_init(&mem, array_size);
	if (err)
		return ERR_PTR(err);

	/* allocate all map elements and zero-initialize them */
	array = bpf_map_area_alloc(array_size, numa_node);
	if (!array) {
		bpf_map_charge_finish(&mem);
		return ERR_PTR(-ENOMEM);
	}

	/* copy mandatory map attributes */
	bpf_map_init_from_attr(&array->map, attr);
	bpf_map_charge_move(&array->map.memory, &mem);

	return &array->map;
}
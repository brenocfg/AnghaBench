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
struct bpf_map {int pages; } ;
struct reuseport_array {struct bpf_map map; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENOMEM ; 
 int EPERM ; 
 struct bpf_map* ERR_PTR (int) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int U32_MAX ; 
 struct reuseport_array* bpf_map_area_alloc (int,int) ; 
 int bpf_map_attr_numa_node (union bpf_attr*) ; 
 int /*<<< orphan*/  bpf_map_init_from_attr (struct bpf_map*,union bpf_attr*) ; 
 int bpf_map_precharge_memlock (int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int round_up (int,int) ; 

__attribute__((used)) static struct bpf_map *reuseport_array_alloc(union bpf_attr *attr)
{
	int err, numa_node = bpf_map_attr_numa_node(attr);
	struct reuseport_array *array;
	u64 cost, array_size;

	if (!capable(CAP_SYS_ADMIN))
		return ERR_PTR(-EPERM);

	array_size = sizeof(*array);
	array_size += (u64)attr->max_entries * sizeof(struct sock *);

	/* make sure there is no u32 overflow later in round_up() */
	cost = array_size;
	if (cost >= U32_MAX - PAGE_SIZE)
		return ERR_PTR(-ENOMEM);
	cost = round_up(cost, PAGE_SIZE) >> PAGE_SHIFT;

	err = bpf_map_precharge_memlock(cost);
	if (err)
		return ERR_PTR(err);

	/* allocate all map elements and zero-initialize them */
	array = bpf_map_area_alloc(array_size, numa_node);
	if (!array)
		return ERR_PTR(-ENOMEM);

	/* copy mandatory map attributes */
	bpf_map_init_from_attr(&array->map, attr);
	array->map.pages = cost;

	return &array->map;
}
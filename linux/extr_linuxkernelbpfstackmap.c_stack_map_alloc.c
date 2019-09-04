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
union bpf_attr {int value_size; int map_flags; scalar_t__ max_entries; int key_size; } ;
typedef  int u64 ;
typedef  int u32 ;
struct stack_map_bucket {int dummy; } ;
struct bpf_map {int value_size; int pages; } ;
struct bpf_stack_map {int n_buckets; struct bpf_map map; } ;
struct bpf_stack_build_id {int dummy; } ;

/* Variables and functions */
 int BPF_F_STACK_BUILD_ID ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int E2BIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 struct bpf_map* ERR_PTR (int) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int STACK_CREATE_FLAG_MASK ; 
 int U32_MAX ; 
 struct bpf_stack_map* bpf_map_area_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_map_area_free (struct bpf_stack_map*) ; 
 int /*<<< orphan*/  bpf_map_attr_numa_node (union bpf_attr*) ; 
 int /*<<< orphan*/  bpf_map_init_from_attr (struct bpf_map*,union bpf_attr*) ; 
 int bpf_map_precharge_memlock (int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int get_callchain_buffers (int) ; 
 int prealloc_elems_and_freelist (struct bpf_stack_map*) ; 
 int /*<<< orphan*/  put_callchain_buffers () ; 
 int round_up (int,int) ; 
 int roundup_pow_of_two (scalar_t__) ; 
 int sysctl_perf_event_max_stack ; 

__attribute__((used)) static struct bpf_map *stack_map_alloc(union bpf_attr *attr)
{
	u32 value_size = attr->value_size;
	struct bpf_stack_map *smap;
	u64 cost, n_buckets;
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return ERR_PTR(-EPERM);

	if (attr->map_flags & ~STACK_CREATE_FLAG_MASK)
		return ERR_PTR(-EINVAL);

	/* check sanity of attributes */
	if (attr->max_entries == 0 || attr->key_size != 4 ||
	    value_size < 8 || value_size % 8)
		return ERR_PTR(-EINVAL);

	BUILD_BUG_ON(sizeof(struct bpf_stack_build_id) % sizeof(u64));
	if (attr->map_flags & BPF_F_STACK_BUILD_ID) {
		if (value_size % sizeof(struct bpf_stack_build_id) ||
		    value_size / sizeof(struct bpf_stack_build_id)
		    > sysctl_perf_event_max_stack)
			return ERR_PTR(-EINVAL);
	} else if (value_size / 8 > sysctl_perf_event_max_stack)
		return ERR_PTR(-EINVAL);

	/* hash table size must be power of 2 */
	n_buckets = roundup_pow_of_two(attr->max_entries);

	cost = n_buckets * sizeof(struct stack_map_bucket *) + sizeof(*smap);
	if (cost >= U32_MAX - PAGE_SIZE)
		return ERR_PTR(-E2BIG);

	smap = bpf_map_area_alloc(cost, bpf_map_attr_numa_node(attr));
	if (!smap)
		return ERR_PTR(-ENOMEM);

	err = -E2BIG;
	cost += n_buckets * (value_size + sizeof(struct stack_map_bucket));
	if (cost >= U32_MAX - PAGE_SIZE)
		goto free_smap;

	bpf_map_init_from_attr(&smap->map, attr);
	smap->map.value_size = value_size;
	smap->n_buckets = n_buckets;
	smap->map.pages = round_up(cost, PAGE_SIZE) >> PAGE_SHIFT;

	err = bpf_map_precharge_memlock(smap->map.pages);
	if (err)
		goto free_smap;

	err = get_callchain_buffers(sysctl_perf_event_max_stack);
	if (err)
		goto free_smap;

	err = prealloc_elems_and_freelist(smap);
	if (err)
		goto put_buffers;

	return &smap->map;

put_buffers:
	put_callchain_buffers();
free_smap:
	bpf_map_area_free(smap);
	return ERR_PTR(err);
}
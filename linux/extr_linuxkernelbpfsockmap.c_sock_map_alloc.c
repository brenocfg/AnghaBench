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
union bpf_attr {scalar_t__ max_entries; int key_size; int value_size; int map_flags; } ;
typedef  int u64 ;
struct sock {int dummy; } ;
struct bpf_map {int max_entries; int pages; int /*<<< orphan*/  numa_node; } ;
struct bpf_stab {struct bpf_map map; int /*<<< orphan*/  sock_map; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 struct bpf_map* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_USER ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int SOCK_CREATE_FLAG_MASK ; 
 int U32_MAX ; 
 int /*<<< orphan*/  bpf_map_area_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_map_init_from_attr (struct bpf_map*,union bpf_attr*) ; 
 int bpf_map_precharge_memlock (int) ; 
 int bpf_tcp_ulp_register () ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bpf_stab*) ; 
 struct bpf_stab* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int round_up (int,int) ; 

__attribute__((used)) static struct bpf_map *sock_map_alloc(union bpf_attr *attr)
{
	struct bpf_stab *stab;
	u64 cost;
	int err;

	if (!capable(CAP_NET_ADMIN))
		return ERR_PTR(-EPERM);

	/* check sanity of attributes */
	if (attr->max_entries == 0 || attr->key_size != 4 ||
	    attr->value_size != 4 || attr->map_flags & ~SOCK_CREATE_FLAG_MASK)
		return ERR_PTR(-EINVAL);

	err = bpf_tcp_ulp_register();
	if (err && err != -EEXIST)
		return ERR_PTR(err);

	stab = kzalloc(sizeof(*stab), GFP_USER);
	if (!stab)
		return ERR_PTR(-ENOMEM);

	bpf_map_init_from_attr(&stab->map, attr);
	raw_spin_lock_init(&stab->lock);

	/* make sure page count doesn't overflow */
	cost = (u64) stab->map.max_entries * sizeof(struct sock *);
	err = -EINVAL;
	if (cost >= U32_MAX - PAGE_SIZE)
		goto free_stab;

	stab->map.pages = round_up(cost, PAGE_SIZE) >> PAGE_SHIFT;

	/* if map size is larger than memlock limit, reject it early */
	err = bpf_map_precharge_memlock(stab->map.pages);
	if (err)
		goto free_stab;

	err = -ENOMEM;
	stab->sock_map = bpf_map_area_alloc(stab->map.max_entries *
					    sizeof(struct sock *),
					    stab->map.numa_node);
	if (!stab->sock_map)
		goto free_stab;

	return &stab->map;
free_stab:
	kfree(stab);
	return ERR_PTR(err);
}
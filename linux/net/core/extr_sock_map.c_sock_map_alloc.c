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
struct bpf_map {int max_entries; int /*<<< orphan*/  memory; int /*<<< orphan*/  numa_node; } ;
struct bpf_stab {struct bpf_map map; scalar_t__ sks; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 struct bpf_map* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_USER ; 
 int SOCK_CREATE_FLAG_MASK ; 
 scalar_t__ bpf_map_area_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_map_charge_finish (int /*<<< orphan*/ *) ; 
 int bpf_map_charge_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bpf_map_init_from_attr (struct bpf_map*,union bpf_attr*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bpf_stab*) ; 
 struct bpf_stab* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bpf_map *sock_map_alloc(union bpf_attr *attr)
{
	struct bpf_stab *stab;
	u64 cost;
	int err;

	if (!capable(CAP_NET_ADMIN))
		return ERR_PTR(-EPERM);
	if (attr->max_entries == 0 ||
	    attr->key_size    != 4 ||
	    attr->value_size  != 4 ||
	    attr->map_flags & ~SOCK_CREATE_FLAG_MASK)
		return ERR_PTR(-EINVAL);

	stab = kzalloc(sizeof(*stab), GFP_USER);
	if (!stab)
		return ERR_PTR(-ENOMEM);

	bpf_map_init_from_attr(&stab->map, attr);
	raw_spin_lock_init(&stab->lock);

	/* Make sure page count doesn't overflow. */
	cost = (u64) stab->map.max_entries * sizeof(struct sock *);
	err = bpf_map_charge_init(&stab->map.memory, cost);
	if (err)
		goto free_stab;

	stab->sks = bpf_map_area_alloc(stab->map.max_entries *
				       sizeof(struct sock *),
				       stab->map.numa_node);
	if (stab->sks)
		return &stab->map;
	err = -ENOMEM;
	bpf_map_charge_finish(&stab->map.memory);
free_stab:
	kfree(stab);
	return ERR_PTR(err);
}
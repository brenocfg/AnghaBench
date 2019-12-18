#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union bpf_attr {scalar_t__ max_entries; scalar_t__ key_size; int value_size; int map_flags; } ;
typedef  int u64 ;
struct bpf_map {int max_entries; int /*<<< orphan*/  numa_node; int /*<<< orphan*/  key_size; } ;
struct bpf_htab_elem {int dummy; } ;
struct bpf_htab_bucket {int dummy; } ;
struct bpf_htab {int buckets_num; struct bpf_map map; TYPE_1__* buckets; scalar_t__ elem_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int E2BIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 struct bpf_map* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_USER ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_BPF_STACK ; 
 int PAGE_SIZE ; 
 int SOCK_CREATE_FLAG_MASK ; 
 int U32_MAX ; 
 TYPE_1__* bpf_map_area_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_map_init_from_attr (struct bpf_map*,union bpf_attr*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bpf_htab*) ; 
 struct bpf_htab* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ round_up (int /*<<< orphan*/ ,int) ; 
 int roundup_pow_of_two (int) ; 

__attribute__((used)) static struct bpf_map *sock_hash_alloc(union bpf_attr *attr)
{
	struct bpf_htab *htab;
	int i, err;
	u64 cost;

	if (!capable(CAP_NET_ADMIN))
		return ERR_PTR(-EPERM);
	if (attr->max_entries == 0 ||
	    attr->key_size    == 0 ||
	    attr->value_size  != 4 ||
	    attr->map_flags & ~SOCK_CREATE_FLAG_MASK)
		return ERR_PTR(-EINVAL);
	if (attr->key_size > MAX_BPF_STACK)
		return ERR_PTR(-E2BIG);

	htab = kzalloc(sizeof(*htab), GFP_USER);
	if (!htab)
		return ERR_PTR(-ENOMEM);

	bpf_map_init_from_attr(&htab->map, attr);

	htab->buckets_num = roundup_pow_of_two(htab->map.max_entries);
	htab->elem_size = sizeof(struct bpf_htab_elem) +
			  round_up(htab->map.key_size, 8);
	if (htab->buckets_num == 0 ||
	    htab->buckets_num > U32_MAX / sizeof(struct bpf_htab_bucket)) {
		err = -EINVAL;
		goto free_htab;
	}

	cost = (u64) htab->buckets_num * sizeof(struct bpf_htab_bucket) +
	       (u64) htab->elem_size * htab->map.max_entries;
	if (cost >= U32_MAX - PAGE_SIZE) {
		err = -EINVAL;
		goto free_htab;
	}

	htab->buckets = bpf_map_area_alloc(htab->buckets_num *
					   sizeof(struct bpf_htab_bucket),
					   htab->map.numa_node);
	if (!htab->buckets) {
		err = -ENOMEM;
		goto free_htab;
	}

	for (i = 0; i < htab->buckets_num; i++) {
		INIT_HLIST_HEAD(&htab->buckets[i].head);
		raw_spin_lock_init(&htab->buckets[i].lock);
	}

	return &htab->map;
free_htab:
	kfree(htab);
	return ERR_PTR(err);
}
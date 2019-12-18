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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct bpf_htab_elem {int /*<<< orphan*/  hash; struct sock* sk; int /*<<< orphan*/  key; } ;
struct TYPE_2__ {scalar_t__ max_entries; int /*<<< orphan*/  numa_node; } ;
struct bpf_htab {int /*<<< orphan*/  count; TYPE_1__ map; int /*<<< orphan*/  elem_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2BIG ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct bpf_htab_elem* ERR_PTR (int /*<<< orphan*/ ) ; 
 int GFP_ATOMIC ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 struct bpf_htab_elem* kmalloc_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bpf_htab_elem *sock_hash_alloc_elem(struct bpf_htab *htab,
						  void *key, u32 key_size,
						  u32 hash, struct sock *sk,
						  struct bpf_htab_elem *old)
{
	struct bpf_htab_elem *new;

	if (atomic_inc_return(&htab->count) > htab->map.max_entries) {
		if (!old) {
			atomic_dec(&htab->count);
			return ERR_PTR(-E2BIG);
		}
	}

	new = kmalloc_node(htab->elem_size, GFP_ATOMIC | __GFP_NOWARN,
			   htab->map.numa_node);
	if (!new) {
		atomic_dec(&htab->count);
		return ERR_PTR(-ENOMEM);
	}
	memcpy(new->key, key, key_size);
	new->sk = sk;
	new->hash = hash;
	return new;
}
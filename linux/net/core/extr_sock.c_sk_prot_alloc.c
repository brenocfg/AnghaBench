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
struct sock {int dummy; } ;
struct proto {int /*<<< orphan*/  owner; int /*<<< orphan*/  obj_size; struct kmem_cache* slab; } ;
struct kmem_cache {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_ZERO ; 
 int /*<<< orphan*/  kfree (struct sock*) ; 
 struct sock* kmalloc (int /*<<< orphan*/ ,int) ; 
 struct sock* kmem_cache_alloc (struct kmem_cache*,int) ; 
 int /*<<< orphan*/  kmem_cache_free (struct kmem_cache*,struct sock*) ; 
 scalar_t__ security_sk_alloc (struct sock*,int,int) ; 
 int /*<<< orphan*/  security_sk_free (struct sock*) ; 
 int /*<<< orphan*/  sk_prot_clear_nulls (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_tx_queue_clear (struct sock*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ want_init_on_alloc (int) ; 

__attribute__((used)) static struct sock *sk_prot_alloc(struct proto *prot, gfp_t priority,
		int family)
{
	struct sock *sk;
	struct kmem_cache *slab;

	slab = prot->slab;
	if (slab != NULL) {
		sk = kmem_cache_alloc(slab, priority & ~__GFP_ZERO);
		if (!sk)
			return sk;
		if (want_init_on_alloc(priority))
			sk_prot_clear_nulls(sk, prot->obj_size);
	} else
		sk = kmalloc(prot->obj_size, priority);

	if (sk != NULL) {
		if (security_sk_alloc(sk, family, priority))
			goto out_free;

		if (!try_module_get(prot->owner))
			goto out_free_sec;
		sk_tx_queue_clear(sk);
	}

	return sk;

out_free_sec:
	security_sk_free(sk);
out_free:
	if (slab != NULL)
		kmem_cache_free(slab, sk);
	else
		kfree(sk);
	return NULL;
}
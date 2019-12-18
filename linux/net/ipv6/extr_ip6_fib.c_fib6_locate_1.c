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
typedef  int /*<<< orphan*/  u8 ;
struct rt6key {int /*<<< orphan*/  addr; } ;
struct in6_addr {int dummy; } ;
struct fib6_node {int fn_bit; int fn_flags; int /*<<< orphan*/  left; int /*<<< orphan*/  right; int /*<<< orphan*/  leaf; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */
 int RTN_RTINFO ; 
 scalar_t__ addr_bit_set (struct in6_addr const*,int) ; 
 int /*<<< orphan*/  ipv6_prefix_equal (int /*<<< orphan*/ *,struct in6_addr const*,int) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fib6_node *fib6_locate_1(struct fib6_node *root,
				       const struct in6_addr *addr,
				       int plen, int offset,
				       bool exact_match)
{
	struct fib6_node *fn, *prev = NULL;

	for (fn = root; fn ; ) {
		struct fib6_info *leaf = rcu_dereference(fn->leaf);
		struct rt6key *key;

		/* This node is being deleted */
		if (!leaf) {
			if (plen <= fn->fn_bit)
				goto out;
			else
				goto next;
		}

		key = (struct rt6key *)((u8 *)leaf + offset);

		/*
		 *	Prefix match
		 */
		if (plen < fn->fn_bit ||
		    !ipv6_prefix_equal(&key->addr, addr, fn->fn_bit))
			goto out;

		if (plen == fn->fn_bit)
			return fn;

		if (fn->fn_flags & RTN_RTINFO)
			prev = fn;

next:
		/*
		 *	We have more bits to go
		 */
		if (addr_bit_set(addr, fn->fn_bit))
			fn = rcu_dereference(fn->right);
		else
			fn = rcu_dereference(fn->left);
	}
out:
	if (exact_match)
		return NULL;
	else
		return prev;
}
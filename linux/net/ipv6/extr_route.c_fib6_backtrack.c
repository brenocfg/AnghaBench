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
struct in6_addr {int dummy; } ;
struct fib6_node {int fn_flags; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct fib6_node* FIB6_SUBTREE (struct fib6_node*) ; 
 int RTN_RTINFO ; 
 int RTN_TL_ROOT ; 
 struct fib6_node* fib6_node_lookup (struct fib6_node*,int /*<<< orphan*/ *,struct in6_addr*) ; 
 struct fib6_node* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fib6_node* fib6_backtrack(struct fib6_node *fn,
					struct in6_addr *saddr)
{
	struct fib6_node *pn, *sn;
	while (1) {
		if (fn->fn_flags & RTN_TL_ROOT)
			return NULL;
		pn = rcu_dereference(fn->parent);
		sn = FIB6_SUBTREE(pn);
		if (sn && sn != fn)
			fn = fib6_node_lookup(sn, NULL, saddr);
		else
			fn = pn;
		if (fn->fn_flags & RTN_RTINFO)
			return fn;
	}
}
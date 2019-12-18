#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* rt6_stats; } ;
struct net {TYPE_2__ ipv6; } ;
struct fib6_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  fib_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  fib6_node_kmem ; 
 struct fib6_node* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fib6_node *node_alloc(struct net *net)
{
	struct fib6_node *fn;

	fn = kmem_cache_zalloc(fib6_node_kmem, GFP_ATOMIC);
	if (fn)
		net->ipv6.rt6_stats->fib_nodes++;

	return fn;
}
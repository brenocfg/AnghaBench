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
struct net {int dummy; } ;
struct fib6_walker {int /*<<< orphan*/  root; int /*<<< orphan*/  node; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWS_INIT ; 
 int fib6_walk_continue (struct fib6_walker*) ; 
 int /*<<< orphan*/  fib6_walker_link (struct net*,struct fib6_walker*) ; 
 int /*<<< orphan*/  fib6_walker_unlink (struct net*,struct fib6_walker*) ; 

__attribute__((used)) static int fib6_walk(struct net *net, struct fib6_walker *w)
{
	int res;

	w->state = FWS_INIT;
	w->node = w->root;

	fib6_walker_link(net, w);
	res = fib6_walk_continue(w);
	if (res <= 0)
		fib6_walker_unlink(net, w);
	return res;
}
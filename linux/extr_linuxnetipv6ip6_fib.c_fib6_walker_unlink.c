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
struct TYPE_2__ {int /*<<< orphan*/  fib6_walker_lock; } ;
struct net {TYPE_1__ ipv6; } ;
struct fib6_walker {int /*<<< orphan*/  lh; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fib6_walker_unlink(struct net *net, struct fib6_walker *w)
{
	write_lock_bh(&net->ipv6.fib6_walker_lock);
	list_del(&w->lh);
	write_unlock_bh(&net->ipv6.fib6_walker_lock);
}
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
struct TYPE_3__ {int ip6_rt_gc_interval; } ;
struct TYPE_4__ {unsigned long ip6_rt_last_gc; int /*<<< orphan*/  fib6_gc_lock; int /*<<< orphan*/  ip6_fib_timer; TYPE_1__ sysctl; } ;
struct net {TYPE_2__ ipv6; } ;
struct fib6_gc_args {int timeout; scalar_t__ more; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fib6_age ; 
 int /*<<< orphan*/  fib6_clean_all (struct net*,int /*<<< orphan*/ ,struct fib6_gc_args*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ round_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_trylock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void fib6_run_gc(unsigned long expires, struct net *net, bool force)
{
	struct fib6_gc_args gc_args;
	unsigned long now;

	if (force) {
		spin_lock_bh(&net->ipv6.fib6_gc_lock);
	} else if (!spin_trylock_bh(&net->ipv6.fib6_gc_lock)) {
		mod_timer(&net->ipv6.ip6_fib_timer, jiffies + HZ);
		return;
	}
	gc_args.timeout = expires ? (int)expires :
			  net->ipv6.sysctl.ip6_rt_gc_interval;
	gc_args.more = 0;

	fib6_clean_all(net, fib6_age, &gc_args);
	now = jiffies;
	net->ipv6.ip6_rt_last_gc = now;

	if (gc_args.more)
		mod_timer(&net->ipv6.ip6_fib_timer,
			  round_jiffies(now
					+ net->ipv6.sysctl.ip6_rt_gc_interval));
	else
		del_timer(&net->ipv6.ip6_fib_timer);
	spin_unlock_bh(&net->ipv6.fib6_gc_lock);
}
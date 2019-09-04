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
struct timer_list {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip6_fib_timer; } ;

/* Variables and functions */
 struct net* arg ; 
 int /*<<< orphan*/  fib6_run_gc (int /*<<< orphan*/ ,struct net*,int) ; 
 struct net* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 TYPE_1__ ipv6 ; 

__attribute__((used)) static void fib6_gc_timer_cb(struct timer_list *t)
{
	struct net *arg = from_timer(arg, t, ipv6.ip6_fib_timer);

	fib6_run_gc(0, arg, true);
}
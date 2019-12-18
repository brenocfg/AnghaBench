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
struct TYPE_2__ {int /*<<< orphan*/  fib6_sernum; } ;
struct net {TYPE_1__ ipv6; } ;

/* Variables and functions */
 int INT_MAX ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fib6_new_sernum(struct net *net)
{
	int new, old;

	do {
		old = atomic_read(&net->ipv6.fib6_sernum);
		new = old < INT_MAX ? old + 1 : 1;
	} while (atomic_cmpxchg(&net->ipv6.fib6_sernum,
				old, new) != old);
	return new;
}
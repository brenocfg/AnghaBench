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

/* Variables and functions */
 int /*<<< orphan*/  FIB6_NO_SERNUM_CHANGE ; 
 int /*<<< orphan*/  __fib6_clean_all (struct net*,int (*) (struct fib6_info*,void*),int /*<<< orphan*/ ,void*,int) ; 

void fib6_clean_all_skip_notify(struct net *net,
				int (*func)(struct fib6_info *, void *),
				void *arg)
{
	__fib6_clean_all(net, func, FIB6_NO_SERNUM_CHANGE, arg, true);
}
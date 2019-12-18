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
struct netpoll {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  __netpoll_cleanup (struct netpoll*) ; 
 int /*<<< orphan*/  kfree (struct netpoll*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void __netpoll_free(struct netpoll *np)
{
	ASSERT_RTNL();

	/* Wait for transmitting packets to finish before freeing. */
	synchronize_rcu();
	__netpoll_cleanup(np);
	kfree(np);
}
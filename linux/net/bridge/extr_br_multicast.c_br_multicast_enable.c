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
struct bridge_mcast_own_query {int /*<<< orphan*/  timer; scalar_t__ startup_sent; } ;

/* Variables and functions */
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ try_to_del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void br_multicast_enable(struct bridge_mcast_own_query *query)
{
	query->startup_sent = 0;

	if (try_to_del_timer_sync(&query->timer) >= 0 ||
	    del_timer(&query->timer))
		mod_timer(&query->timer, jiffies);
}
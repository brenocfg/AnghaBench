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
struct tipc_discoverer {int /*<<< orphan*/  skb; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tipc_discoverer*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 

void tipc_disc_delete(struct tipc_discoverer *d)
{
	del_timer_sync(&d->timer);
	kfree_skb(d->skb);
	kfree(d);
}
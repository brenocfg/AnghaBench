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
struct TYPE_3__ {scalar_t__ timeout; } ;
struct TYPE_4__ {TYPE_1__ s; } ;
struct tipc_subscription {int /*<<< orphan*/  sub_list; int /*<<< orphan*/  timer; TYPE_2__ evt; } ;

/* Variables and functions */
 scalar_t__ TIPC_WAIT_FOREVER ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_nametbl_unsubscribe (struct tipc_subscription*) ; 
 int /*<<< orphan*/  tipc_sub_put (struct tipc_subscription*) ; 

void tipc_sub_unsubscribe(struct tipc_subscription *sub)
{
	tipc_nametbl_unsubscribe(sub);
	if (sub->evt.s.timeout != TIPC_WAIT_FOREVER)
		del_timer_sync(&sub->timer);
	list_del(&sub->sub_list);
	tipc_sub_put(sub);
}
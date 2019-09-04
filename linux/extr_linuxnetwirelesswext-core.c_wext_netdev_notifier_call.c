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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_OK ; 
 int /*<<< orphan*/  wireless_nlevent_flush () ; 

__attribute__((used)) static int wext_netdev_notifier_call(struct notifier_block *nb,
				     unsigned long state, void *ptr)
{
	/*
	 * When a netdev changes state in any way, flush all pending messages
	 * to avoid them going out in a strange order, e.g. RTM_NEWLINK after
	 * RTM_DELLINK, or with IFF_UP after without IFF_UP during dev_close()
	 * or similar - all of which could otherwise happen due to delays from
	 * schedule_work().
	 */
	wireless_nlevent_flush();

	return NOTIFY_OK;
}
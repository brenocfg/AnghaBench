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
struct timer_list {int dummy; } ;
struct sis190_private {int /*<<< orphan*/  phy_task; struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct sis190_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 
 struct sis190_private* tp ; 

__attribute__((used)) static void sis190_phy_timer(struct timer_list *t)
{
	struct sis190_private *tp = from_timer(tp, t, timer);
	struct net_device *dev = tp->dev;

	if (likely(netif_running(dev)))
		schedule_work(&tp->phy_task);
}
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
struct timer_list {scalar_t__ expires; } ;
struct sis190_private {struct timer_list timer; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SIS190_PHY_TIMEOUT ; 
 int /*<<< orphan*/  add_timer (struct timer_list*) ; 
 scalar_t__ jiffies ; 
 struct sis190_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sis190_phy_timer ; 
 int /*<<< orphan*/  timer_setup (struct timer_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sis190_request_timer(struct net_device *dev)
{
	struct sis190_private *tp = netdev_priv(dev);
	struct timer_list *timer = &tp->timer;

	timer_setup(timer, sis190_phy_timer, 0);
	timer->expires = jiffies + SIS190_PHY_TIMEOUT;
	add_timer(timer);
}
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
struct net_device_stats {int dummy; } ;
struct net_device {struct net_device_stats stats; } ;
struct happy_meal {int /*<<< orphan*/  happy_lock; int /*<<< orphan*/  bigmacregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  happy_meal_get_counters (struct happy_meal*,int /*<<< orphan*/ ) ; 
 struct happy_meal* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct net_device_stats *happy_meal_get_stats(struct net_device *dev)
{
	struct happy_meal *hp = netdev_priv(dev);

	spin_lock_irq(&hp->happy_lock);
	happy_meal_get_counters(hp, hp->bigmacregs);
	spin_unlock_irq(&hp->happy_lock);

	return &dev->stats;
}
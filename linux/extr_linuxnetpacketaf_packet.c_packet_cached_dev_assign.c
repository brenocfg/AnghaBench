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
struct packet_sock {int /*<<< orphan*/  cached_dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct net_device*) ; 

__attribute__((used)) static void packet_cached_dev_assign(struct packet_sock *po,
				     struct net_device *dev)
{
	rcu_assign_pointer(po->cached_dev, dev);
}
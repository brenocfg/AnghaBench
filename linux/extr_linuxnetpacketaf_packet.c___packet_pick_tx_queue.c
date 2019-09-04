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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_pick_tx_cpu_id (struct net_device*,struct sk_buff*,struct net_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 __packet_pick_tx_queue(struct net_device *dev, struct sk_buff *skb,
				  struct net_device *sb_dev)
{
	return dev_pick_tx_cpu_id(dev, skb, sb_dev, NULL);
}
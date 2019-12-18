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
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int real_num_tx_queues; } ;

/* Variables and functions */
 scalar_t__ raw_smp_processor_id () ; 

u16 dev_pick_tx_cpu_id(struct net_device *dev, struct sk_buff *skb,
		       struct net_device *sb_dev)
{
	return (u16)raw_smp_processor_id() % dev->real_num_tx_queues;
}
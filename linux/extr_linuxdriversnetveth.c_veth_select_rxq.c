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
struct net_device {int real_num_rx_queues; } ;

/* Variables and functions */
 int smp_processor_id () ; 

__attribute__((used)) static int veth_select_rxq(struct net_device *dev)
{
	return smp_processor_id() % dev->real_num_rx_queues;
}
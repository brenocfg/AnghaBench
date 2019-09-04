#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  adapter_deliver; int /*<<< orphan*/  adapter_intr; int /*<<< orphan*/  adapter_enable_int; } ;
struct aac_dev {TYPE_1__ a_ops; } ;

/* Variables and functions */
#define  AAC_COMM_MESSAGE 129 
#define  AAC_COMM_PRODUCER 128 
 int /*<<< orphan*/  aac_rx_deliver_message ; 
 int /*<<< orphan*/  aac_rx_deliver_producer ; 
 int /*<<< orphan*/  aac_rx_enable_interrupt_message ; 
 int /*<<< orphan*/  aac_rx_enable_interrupt_producer ; 
 int /*<<< orphan*/  aac_rx_intr_message ; 
 int /*<<< orphan*/  aac_rx_intr_producer ; 

int aac_rx_select_comm(struct aac_dev *dev, int comm)
{
	switch (comm) {
	case AAC_COMM_PRODUCER:
		dev->a_ops.adapter_enable_int = aac_rx_enable_interrupt_producer;
		dev->a_ops.adapter_intr = aac_rx_intr_producer;
		dev->a_ops.adapter_deliver = aac_rx_deliver_producer;
		break;
	case AAC_COMM_MESSAGE:
		dev->a_ops.adapter_enable_int = aac_rx_enable_interrupt_message;
		dev->a_ops.adapter_intr = aac_rx_intr_message;
		dev->a_ops.adapter_deliver = aac_rx_deliver_message;
		break;
	default:
		return 1;
	}
	return 0;
}
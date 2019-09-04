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
struct ntb_transport_qp {unsigned int tx_index; unsigned int tx_max_entry; TYPE_1__* remote_rx_info; } ;
struct TYPE_2__ {unsigned int entry; } ;

/* Variables and functions */

unsigned int ntb_transport_tx_free_entry(struct ntb_transport_qp *qp)
{
	unsigned int head = qp->tx_index;
	unsigned int tail = qp->remote_rx_info->entry;

	return tail > head ? tail - head : qp->tx_max_entry + tail - head;
}
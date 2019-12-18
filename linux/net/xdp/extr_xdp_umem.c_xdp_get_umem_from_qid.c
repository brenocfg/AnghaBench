#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct xdp_umem {int dummy; } ;
struct net_device {size_t real_num_rx_queues; size_t real_num_tx_queues; TYPE_2__* _tx; TYPE_1__* _rx; } ;
struct TYPE_4__ {struct xdp_umem* umem; } ;
struct TYPE_3__ {struct xdp_umem* umem; } ;

/* Variables and functions */

struct xdp_umem *xdp_get_umem_from_qid(struct net_device *dev,
				       u16 queue_id)
{
	if (queue_id < dev->real_num_rx_queues)
		return dev->_rx[queue_id].umem;
	if (queue_id < dev->real_num_tx_queues)
		return dev->_tx[queue_id].umem;

	return NULL;
}
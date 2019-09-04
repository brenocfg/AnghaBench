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
struct ntb_transport_qp {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int __ntb_netdev_maybe_stop_tx (struct net_device*,struct ntb_transport_qp*,int) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int ntb_transport_tx_free_entry (struct ntb_transport_qp*) ; 

__attribute__((used)) static int ntb_netdev_maybe_stop_tx(struct net_device *ndev,
				    struct ntb_transport_qp *qp, int size)
{
	if (netif_queue_stopped(ndev) ||
	    (ntb_transport_tx_free_entry(qp) >= size))
		return 0;

	return __ntb_netdev_maybe_stop_tx(ndev, qp, size);
}
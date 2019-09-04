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
struct rocker_port {int /*<<< orphan*/  napi_tx; int /*<<< orphan*/  napi_rx; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct rocker_port*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct rocker_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  rocker_msix_rx_vector (struct rocker_port*) ; 
 int /*<<< orphan*/  rocker_msix_tx_vector (struct rocker_port*) ; 
 int /*<<< orphan*/  rocker_port_dma_rings_fini (struct rocker_port*) ; 
 int /*<<< orphan*/  rocker_port_set_enable (struct rocker_port*,int) ; 
 int /*<<< orphan*/  rocker_world_port_stop (struct rocker_port*) ; 

__attribute__((used)) static int rocker_port_stop(struct net_device *dev)
{
	struct rocker_port *rocker_port = netdev_priv(dev);

	netif_stop_queue(dev);
	rocker_port_set_enable(rocker_port, false);
	napi_disable(&rocker_port->napi_rx);
	napi_disable(&rocker_port->napi_tx);
	rocker_world_port_stop(rocker_port);
	free_irq(rocker_msix_rx_vector(rocker_port), rocker_port);
	free_irq(rocker_msix_tx_vector(rocker_port), rocker_port);
	rocker_port_dma_rings_fini(rocker_port);

	return 0;
}
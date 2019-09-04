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
struct rocker_port {int /*<<< orphan*/  napi_rx; int /*<<< orphan*/  napi_tx; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  proto_down; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct rocker_port*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct rocker_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rocker_port*) ; 
 int /*<<< orphan*/  rocker_driver_name ; 
 int /*<<< orphan*/  rocker_msix_rx_vector (struct rocker_port*) ; 
 int /*<<< orphan*/  rocker_msix_tx_vector (struct rocker_port*) ; 
 int /*<<< orphan*/  rocker_port_dma_rings_fini (struct rocker_port*) ; 
 int rocker_port_dma_rings_init (struct rocker_port*) ; 
 int /*<<< orphan*/  rocker_port_set_enable (struct rocker_port*,int) ; 
 int /*<<< orphan*/  rocker_rx_irq_handler ; 
 int /*<<< orphan*/  rocker_tx_irq_handler ; 
 int rocker_world_port_open (struct rocker_port*) ; 

__attribute__((used)) static int rocker_port_open(struct net_device *dev)
{
	struct rocker_port *rocker_port = netdev_priv(dev);
	int err;

	err = rocker_port_dma_rings_init(rocker_port);
	if (err)
		return err;

	err = request_irq(rocker_msix_tx_vector(rocker_port),
			  rocker_tx_irq_handler, 0,
			  rocker_driver_name, rocker_port);
	if (err) {
		netdev_err(rocker_port->dev, "cannot assign tx irq\n");
		goto err_request_tx_irq;
	}

	err = request_irq(rocker_msix_rx_vector(rocker_port),
			  rocker_rx_irq_handler, 0,
			  rocker_driver_name, rocker_port);
	if (err) {
		netdev_err(rocker_port->dev, "cannot assign rx irq\n");
		goto err_request_rx_irq;
	}

	err = rocker_world_port_open(rocker_port);
	if (err) {
		netdev_err(rocker_port->dev, "cannot open port in world\n");
		goto err_world_port_open;
	}

	napi_enable(&rocker_port->napi_tx);
	napi_enable(&rocker_port->napi_rx);
	if (!dev->proto_down)
		rocker_port_set_enable(rocker_port, true);
	netif_start_queue(dev);
	return 0;

err_world_port_open:
	free_irq(rocker_msix_rx_vector(rocker_port), rocker_port);
err_request_rx_irq:
	free_irq(rocker_msix_tx_vector(rocker_port), rocker_port);
err_request_tx_irq:
	rocker_port_dma_rings_fini(rocker_port);
	return err;
}
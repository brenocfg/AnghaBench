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
struct platform_device {int dummy; } ;
struct octeon_ethernet {int /*<<< orphan*/  port_periodic_work; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CVMX_FPA_OUTPUT_BUFFER_POOL ; 
 int /*<<< orphan*/  CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE ; 
 scalar_t__ CVMX_FPA_PACKET_POOL ; 
 int /*<<< orphan*/  CVMX_FPA_PACKET_POOL_SIZE ; 
 scalar_t__ CVMX_FPA_WQE_POOL ; 
 int /*<<< orphan*/  CVMX_FPA_WQE_POOL_SIZE ; 
 int TOTAL_NUMBER_OF_PORTS ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct net_device** cvm_oct_device ; 
 int /*<<< orphan*/  cvm_oct_mem_empty_fpa (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cvm_oct_poll_queue_stopping ; 
 int /*<<< orphan*/  cvm_oct_rx_refill_work ; 
 int /*<<< orphan*/  cvm_oct_rx_shutdown () ; 
 int /*<<< orphan*/  cvm_oct_tx_shutdown () ; 
 int /*<<< orphan*/  cvm_oct_tx_shutdown_dev (struct net_device*) ; 
 int /*<<< orphan*/  cvmx_ipd_disable () ; 
 int /*<<< orphan*/  cvmx_ipd_free_ptr () ; 
 int /*<<< orphan*/  cvmx_pko_disable () ; 
 int /*<<< orphan*/  cvmx_pko_shutdown () ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct octeon_ethernet* netdev_priv (struct net_device*) ; 
 int num_packet_buffers ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int cvm_oct_remove(struct platform_device *pdev)
{
	int port;

	cvmx_ipd_disable();

	atomic_inc_return(&cvm_oct_poll_queue_stopping);
	cancel_delayed_work_sync(&cvm_oct_rx_refill_work);

	cvm_oct_rx_shutdown();
	cvm_oct_tx_shutdown();

	cvmx_pko_disable();

	/* Free the ethernet devices */
	for (port = 0; port < TOTAL_NUMBER_OF_PORTS; port++) {
		if (cvm_oct_device[port]) {
			struct net_device *dev = cvm_oct_device[port];
			struct octeon_ethernet *priv = netdev_priv(dev);

			cancel_delayed_work_sync(&priv->port_periodic_work);

			cvm_oct_tx_shutdown_dev(dev);
			unregister_netdev(dev);
			free_netdev(dev);
			cvm_oct_device[port] = NULL;
		}
	}

	cvmx_pko_shutdown();

	cvmx_ipd_free_ptr();

	/* Free the HW pools */
	cvm_oct_mem_empty_fpa(CVMX_FPA_PACKET_POOL, CVMX_FPA_PACKET_POOL_SIZE,
			      num_packet_buffers);
	cvm_oct_mem_empty_fpa(CVMX_FPA_WQE_POOL, CVMX_FPA_WQE_POOL_SIZE,
			      num_packet_buffers);
	if (CVMX_FPA_OUTPUT_BUFFER_POOL != CVMX_FPA_PACKET_POOL)
		cvm_oct_mem_empty_fpa(CVMX_FPA_OUTPUT_BUFFER_POOL,
				      CVMX_FPA_OUTPUT_BUFFER_POOL_SIZE, 128);
	return 0;
}
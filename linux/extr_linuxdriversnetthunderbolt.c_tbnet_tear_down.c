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
struct TYPE_2__ {int /*<<< orphan*/  ring; } ;
struct tbnet {int login_sent; int login_received; int /*<<< orphan*/  connection_lock; scalar_t__ login_retries; int /*<<< orphan*/  dev; int /*<<< orphan*/  xd; TYPE_1__ tx_ring; TYPE_1__ rx_ring; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int TBNET_LOGOUT_RETRIES ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_login (struct tbnet*) ; 
 int /*<<< orphan*/  tb_ring_stop (int /*<<< orphan*/ ) ; 
 scalar_t__ tb_xdomain_disable_paths (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbnet_free_buffers (TYPE_1__*) ; 
 int tbnet_logout_request (struct tbnet*) ; 

__attribute__((used)) static void tbnet_tear_down(struct tbnet *net, bool send_logout)
{
	netif_carrier_off(net->dev);
	netif_stop_queue(net->dev);

	stop_login(net);

	mutex_lock(&net->connection_lock);

	if (net->login_sent && net->login_received) {
		int retries = TBNET_LOGOUT_RETRIES;

		while (send_logout && retries-- > 0) {
			int ret = tbnet_logout_request(net);
			if (ret != -ETIMEDOUT)
				break;
		}

		tb_ring_stop(net->rx_ring.ring);
		tb_ring_stop(net->tx_ring.ring);
		tbnet_free_buffers(&net->rx_ring);
		tbnet_free_buffers(&net->tx_ring);

		if (tb_xdomain_disable_paths(net->xd))
			netdev_warn(net->dev, "failed to disable DMA paths\n");
	}

	net->login_retries = 0;
	net->login_sent = false;
	net->login_received = false;

	mutex_unlock(&net->connection_lock);
}
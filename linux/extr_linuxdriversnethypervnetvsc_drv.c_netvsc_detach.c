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
struct netvsc_device {int num_chn; int /*<<< orphan*/  subchan_work; } ;
struct net_device_context {struct hv_device* device_ctx; } ;
struct net_device {int dummy; } ;
struct hv_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netvsc_tx_disable (struct netvsc_device*,struct net_device*) ; 
 int netvsc_wait_until_empty (struct netvsc_device*) ; 
 int rndis_filter_close (struct netvsc_device*) ; 
 int /*<<< orphan*/  rndis_filter_device_remove (struct hv_device*,struct netvsc_device*) ; 

__attribute__((used)) static int netvsc_detach(struct net_device *ndev,
			 struct netvsc_device *nvdev)
{
	struct net_device_context *ndev_ctx = netdev_priv(ndev);
	struct hv_device *hdev = ndev_ctx->device_ctx;
	int ret;

	/* Don't try continuing to try and setup sub channels */
	if (cancel_work_sync(&nvdev->subchan_work))
		nvdev->num_chn = 1;

	/* If device was up (receiving) then shutdown */
	if (netif_running(ndev)) {
		netvsc_tx_disable(nvdev, ndev);

		ret = rndis_filter_close(nvdev);
		if (ret) {
			netdev_err(ndev,
				   "unable to close device (ret %d).\n", ret);
			return ret;
		}

		ret = netvsc_wait_until_empty(nvdev);
		if (ret) {
			netdev_err(ndev,
				   "Ring buffer not empty after closing rndis\n");
			return ret;
		}
	}

	netif_device_detach(ndev);

	rndis_filter_device_remove(hdev, nvdev);

	return 0;
}
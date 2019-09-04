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
struct virtnet_info {int max_queue_pairs; TYPE_2__* sq; TYPE_1__* rq; int /*<<< orphan*/  dev; int /*<<< orphan*/  refill; int /*<<< orphan*/  config_work; } ;
struct virtio_device {struct virtnet_info* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  napi; } ;
struct TYPE_3__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtnet_napi_tx_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virtnet_freeze_down(struct virtio_device *vdev)
{
	struct virtnet_info *vi = vdev->priv;
	int i;

	/* Make sure no work handler is accessing the device */
	flush_work(&vi->config_work);

	netif_tx_lock_bh(vi->dev);
	netif_device_detach(vi->dev);
	netif_tx_unlock_bh(vi->dev);
	cancel_delayed_work_sync(&vi->refill);

	if (netif_running(vi->dev)) {
		for (i = 0; i < vi->max_queue_pairs; i++) {
			napi_disable(&vi->rq[i].napi);
			virtnet_napi_tx_disable(&vi->sq[i].napi);
		}
	}
}
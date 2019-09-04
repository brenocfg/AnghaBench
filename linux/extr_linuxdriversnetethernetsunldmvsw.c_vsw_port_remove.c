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
struct TYPE_4__ {int /*<<< orphan*/  timer; } ;
struct vnet_port {int /*<<< orphan*/  dev; TYPE_2__ vio; int /*<<< orphan*/  napi; TYPE_1__* vp; int /*<<< orphan*/  list; int /*<<< orphan*/  clean_timer; } ;
struct vio_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct vnet_port* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sunvnet_port_free_tx_bufs_common (struct vnet_port*) ; 
 int /*<<< orphan*/  sunvnet_port_rm_txq_common (struct vnet_port*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vio_ldc_free (TYPE_2__*) ; 

__attribute__((used)) static int vsw_port_remove(struct vio_dev *vdev)
{
	struct vnet_port *port = dev_get_drvdata(&vdev->dev);
	unsigned long flags;

	if (port) {
		del_timer_sync(&port->vio.timer);
		del_timer_sync(&port->clean_timer);

		napi_disable(&port->napi);
		unregister_netdev(port->dev);

		list_del_rcu(&port->list);

		synchronize_rcu();
		spin_lock_irqsave(&port->vp->lock, flags);
		sunvnet_port_rm_txq_common(port);
		spin_unlock_irqrestore(&port->vp->lock, flags);
		netif_napi_del(&port->napi);
		sunvnet_port_free_tx_bufs_common(port);
		vio_ldc_free(&port->vio);

		dev_set_drvdata(&vdev->dev, NULL);

		free_netdev(port->dev);
	}

	return 0;
}
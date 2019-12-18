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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct panda_inf_priv {TYPE_1__ can; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 struct panda_inf_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  panda_urb_unlink (struct panda_inf_priv*) ; 

__attribute__((used)) static int panda_usb_close(struct net_device *netdev)
{
  struct panda_inf_priv *priv = netdev_priv(netdev);

  priv->can.state = CAN_STATE_STOPPED;

  netif_stop_queue(netdev);

  /* Stop polling */
  panda_urb_unlink(priv);

  close_candev(netdev);

  return 0;
}
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
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 struct panda_inf_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 

__attribute__((used)) static int panda_usb_open(struct net_device *netdev)
{
  struct panda_inf_priv *priv = netdev_priv(netdev);
  int err;

  /* common open */
  err = open_candev(netdev);
  if (err)
    return err;

  //priv->can_speed_check = true;
  priv->can.state = CAN_STATE_ERROR_ACTIVE;

  netif_start_queue(netdev);

  return 0;
}
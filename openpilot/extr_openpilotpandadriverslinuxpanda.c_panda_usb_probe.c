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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bitrate; } ;
struct TYPE_4__ {TYPE_1__ bittiming; int /*<<< orphan*/  state; } ;
struct panda_inf_priv {int interface_num; struct net_device* netdev; TYPE_2__ can; int /*<<< orphan*/  tx_submitted; int /*<<< orphan*/  mcu_can_ifnum; struct panda_dev_priv* priv_dev; } ;
struct panda_dev_priv {struct panda_inf_priv** interfaces; int /*<<< orphan*/  rx_submitted; int /*<<< orphan*/ * dev; struct usb_device* udev; } ;
struct net_device {int /*<<< orphan*/  flags; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFF_ECHO ; 
 int /*<<< orphan*/  PANDA_BITRATE ; 
 int /*<<< orphan*/  PANDA_MAX_TX_URBS ; 
 int PANDA_NUM_CAN_INTERFACES ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_candev (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * can_numbering ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct panda_dev_priv*) ; 
 struct panda_dev_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct panda_inf_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  panda_netdev_ops ; 
 int panda_set_output_enable (struct panda_inf_priv*,int) ; 
 int panda_usb_start (struct panda_dev_priv*) ; 
 int register_candev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_candev (struct net_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct panda_dev_priv*) ; 

__attribute__((used)) static int panda_usb_probe(struct usb_interface *intf,
			   const struct usb_device_id *id)
{
  struct net_device *netdev;
  struct panda_inf_priv *priv_inf;
  int err = -ENOMEM;
  int inf_num;
  struct panda_dev_priv *priv_dev;
  struct usb_device *usbdev = interface_to_usbdev(intf);

  priv_dev = kzalloc(sizeof(struct panda_dev_priv), GFP_KERNEL);
  if (!priv_dev) {
    dev_err(&intf->dev, "Couldn't alloc priv_dev\n");
    return -ENOMEM;
  }
  priv_dev->udev = usbdev;
  priv_dev->dev = &intf->dev;
  usb_set_intfdata(intf, priv_dev);

  ////// Interface privs
  for(inf_num = 0; inf_num < PANDA_NUM_CAN_INTERFACES; inf_num++){
    netdev = alloc_candev(sizeof(struct panda_inf_priv), PANDA_MAX_TX_URBS);
    if (!netdev) {
      dev_err(&intf->dev, "Couldn't alloc candev\n");
      goto cleanup_candev;
    }
    netdev->netdev_ops = &panda_netdev_ops;
    netdev->flags |= IFF_ECHO; /* we support local echo */

    priv_inf = netdev_priv(netdev);
    priv_inf->netdev = netdev;
    priv_inf->priv_dev = priv_dev;
    priv_inf->interface_num = inf_num;
    priv_inf->mcu_can_ifnum = can_numbering[inf_num];

    init_usb_anchor(&priv_dev->rx_submitted);
    init_usb_anchor(&priv_inf->tx_submitted);

    /* Init CAN device */
    priv_inf->can.state = CAN_STATE_STOPPED;
    priv_inf->can.bittiming.bitrate = PANDA_BITRATE;

    SET_NETDEV_DEV(netdev, &intf->dev);

    err = register_candev(netdev);
    if (err) {
      netdev_err(netdev, "couldn't register PANDA CAN device: %d\n", err);
      free_candev(priv_inf->netdev);
      goto cleanup_candev;
    }

    priv_dev->interfaces[inf_num] = priv_inf;
  }

  err = panda_usb_start(priv_dev);
  if (err) {
    dev_err(&intf->dev, "Failed to initialize Comma.ai Panda CAN controller\n");
    goto cleanup_candev;
  }

  err = panda_set_output_enable(priv_inf, true);
  if (err) {
    dev_info(&intf->dev, "Failed to initialize send enable message to Panda.\n");
    goto cleanup_candev;
  }

  dev_info(&intf->dev, "Comma.ai Panda CAN controller connected\n");

  return 0;

 cleanup_candev:
  for(inf_num = 0; inf_num < PANDA_NUM_CAN_INTERFACES; inf_num++){
    priv_inf = priv_dev->interfaces[inf_num];
    if(priv_inf){
      unregister_candev(priv_inf->netdev);
      free_candev(priv_inf->netdev);
    }else
      break;
  }

  kfree(priv_dev);

  return err;
}
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
struct usb_interface {int dummy; } ;
struct panda_inf_priv {int /*<<< orphan*/  netdev; } ;
struct panda_dev_priv {struct panda_inf_priv** interfaces; } ;

/* Variables and functions */
 int PANDA_NUM_CAN_INTERFACES ; 
 int /*<<< orphan*/  free_candev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct panda_dev_priv*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  panda_urb_unlink (struct panda_inf_priv*) ; 
 int /*<<< orphan*/  unregister_candev (int /*<<< orphan*/ ) ; 
 struct panda_dev_priv* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void panda_usb_disconnect(struct usb_interface *intf)
{
  struct panda_dev_priv *priv_dev = usb_get_intfdata(intf);
  struct panda_inf_priv *priv_inf;
  int inf_num;

  usb_set_intfdata(intf, NULL);

  for(inf_num = 0; inf_num < PANDA_NUM_CAN_INTERFACES; inf_num++){
    priv_inf = priv_dev->interfaces[inf_num];
    if(priv_inf){
      netdev_info(priv_inf->netdev, "device disconnected\n");
      unregister_candev(priv_inf->netdev);
      free_candev(priv_inf->netdev);
    }else
      break;
  }

  panda_urb_unlink(priv_inf);
  kfree(priv_dev);
}
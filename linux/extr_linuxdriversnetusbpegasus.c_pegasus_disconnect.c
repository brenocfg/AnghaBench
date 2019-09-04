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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct pegasus {int /*<<< orphan*/  net; int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/  carrier_check; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PEGASUS_UNPLUG ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_all_urbs (struct pegasus*) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pegasus_dec_workqueue () ; 
 int /*<<< orphan*/  unlink_all_urbs (struct pegasus*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 struct pegasus* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pegasus_disconnect(struct usb_interface *intf)
{
	struct pegasus *pegasus = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);
	if (!pegasus) {
		dev_dbg(&intf->dev, "unregistering non-bound device?\n");
		return;
	}

	pegasus->flags |= PEGASUS_UNPLUG;
	cancel_delayed_work(&pegasus->carrier_check);
	unregister_netdev(pegasus->net);
	unlink_all_urbs(pegasus);
	free_all_urbs(pegasus);
	if (pegasus->rx_skb != NULL) {
		dev_kfree_skb(pegasus->rx_skb);
		pegasus->rx_skb = NULL;
	}
	free_netdev(pegasus->net);
	pegasus_dec_workqueue();
}
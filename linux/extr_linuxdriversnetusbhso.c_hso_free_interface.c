#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct rfkill {int dummy; } ;
struct hso_serial {TYPE_1__* parent; int /*<<< orphan*/  port; } ;
struct TYPE_12__ {int /*<<< orphan*/  net; struct rfkill* rfkill; } ;
struct TYPE_11__ {int /*<<< orphan*/  async_get_intf; int /*<<< orphan*/  async_put_intf; struct usb_interface* interface; } ;
struct TYPE_10__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  async_get_intf; int /*<<< orphan*/  async_put_intf; struct usb_interface* interface; } ;
struct TYPE_9__ {int usb_gone; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int HSO_MAX_NET_DEVICES ; 
 int HSO_SERIAL_TTY_MINORS ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 TYPE_7__* dev2net (TYPE_3__*) ; 
 struct hso_serial* dev2ser (TYPE_2__*) ; 
 int /*<<< orphan*/  hso_free_net_device (TYPE_3__*) ; 
 int /*<<< orphan*/  hso_serial_ref_free ; 
 int /*<<< orphan*/  hso_serial_tty_unregister (struct hso_serial*) ; 
 int /*<<< orphan*/  hso_stop_net_device (TYPE_3__*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 TYPE_3__** network_table ; 
 int /*<<< orphan*/  rfkill_destroy (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_unregister (struct rfkill*) ; 
 TYPE_2__** serial_table ; 
 int /*<<< orphan*/  set_serial_by_index (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_tty_hangup (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hso_free_interface(struct usb_interface *interface)
{
	struct hso_serial *serial;
	int i;

	for (i = 0; i < HSO_SERIAL_TTY_MINORS; i++) {
		if (serial_table[i] &&
		    (serial_table[i]->interface == interface)) {
			serial = dev2ser(serial_table[i]);
			tty_port_tty_hangup(&serial->port, false);
			mutex_lock(&serial->parent->mutex);
			serial->parent->usb_gone = 1;
			mutex_unlock(&serial->parent->mutex);
			cancel_work_sync(&serial_table[i]->async_put_intf);
			cancel_work_sync(&serial_table[i]->async_get_intf);
			hso_serial_tty_unregister(serial);
			kref_put(&serial_table[i]->ref, hso_serial_ref_free);
			set_serial_by_index(i, NULL);
		}
	}

	for (i = 0; i < HSO_MAX_NET_DEVICES; i++) {
		if (network_table[i] &&
		    (network_table[i]->interface == interface)) {
			struct rfkill *rfk = dev2net(network_table[i])->rfkill;
			/* hso_stop_net_device doesn't stop the net queue since
			 * traffic needs to start it again when suspended */
			netif_stop_queue(dev2net(network_table[i])->net);
			hso_stop_net_device(network_table[i]);
			cancel_work_sync(&network_table[i]->async_put_intf);
			cancel_work_sync(&network_table[i]->async_get_intf);
			if (rfk) {
				rfkill_unregister(rfk);
				rfkill_destroy(rfk);
			}
			hso_free_net_device(network_table[i]);
		}
	}
}
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
struct bcd2000 {int /*<<< orphan*/  card; int /*<<< orphan*/  card_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcd2000_free_usb_related_resources (struct bcd2000*,struct usb_interface*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devices_mutex ; 
 int /*<<< orphan*/  devices_used ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_card_free_when_closed (int /*<<< orphan*/ ) ; 
 struct bcd2000* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void bcd2000_disconnect(struct usb_interface *interface)
{
	struct bcd2000 *bcd2k = usb_get_intfdata(interface);

	if (!bcd2k)
		return;

	mutex_lock(&devices_mutex);

	/* make sure that userspace cannot create new requests */
	snd_card_disconnect(bcd2k->card);

	bcd2000_free_usb_related_resources(bcd2k, interface);

	clear_bit(bcd2k->card_index, devices_used);

	snd_card_free_when_closed(bcd2k->card);

	mutex_unlock(&devices_mutex);
}
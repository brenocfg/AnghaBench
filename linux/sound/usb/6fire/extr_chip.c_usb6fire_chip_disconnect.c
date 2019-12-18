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
struct sfire_chip {size_t regidx; int shutdown; int /*<<< orphan*/  intf_count; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** chips ; 
 int /*<<< orphan*/ ** devices ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_mutex ; 
 int /*<<< orphan*/  usb6fire_chip_abort (struct sfire_chip*) ; 
 int /*<<< orphan*/  usb6fire_chip_destroy (struct sfire_chip*) ; 
 struct sfire_chip* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void usb6fire_chip_disconnect(struct usb_interface *intf)
{
	struct sfire_chip *chip;

	chip = usb_get_intfdata(intf);
	if (chip) { /* if !chip, fw upload has been performed */
		chip->intf_count--;
		if (!chip->intf_count) {
			mutex_lock(&register_mutex);
			devices[chip->regidx] = NULL;
			chips[chip->regidx] = NULL;
			mutex_unlock(&register_mutex);

			chip->shutdown = true;
			usb6fire_chip_abort(chip);
			usb6fire_chip_destroy(chip);
		}
	}
}
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
struct snd_card {int dummy; } ;
struct hiface_chip {struct snd_card* card; } ;

/* Variables and functions */
 int /*<<< orphan*/  hiface_pcm_abort (struct hiface_chip*) ; 
 int /*<<< orphan*/  snd_card_disconnect (struct snd_card*) ; 
 int /*<<< orphan*/  snd_card_free_when_closed (struct snd_card*) ; 
 struct hiface_chip* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void hiface_chip_disconnect(struct usb_interface *intf)
{
	struct hiface_chip *chip;
	struct snd_card *card;

	chip = usb_get_intfdata(intf);
	if (!chip)
		return;

	card = chip->card;

	/* Make sure that the userspace cannot create new request */
	snd_card_disconnect(card);

	hiface_pcm_abort(chip);
	snd_card_free_when_closed(card);
}
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
struct usb_function {TYPE_1__* config; } ;
struct usb_configuration {int dummy; } ;
struct usb_composite_dev {int dummy; } ;
struct snd_card {int dummy; } ;
struct f_midi {struct snd_card* card; } ;
struct TYPE_2__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*) ; 
 int /*<<< orphan*/  f_midi_disable (struct usb_function*) ; 
 struct f_midi* func_to_midi (struct usb_function*) ; 
 int /*<<< orphan*/  snd_card_free_when_closed (struct snd_card*) ; 
 int /*<<< orphan*/  usb_free_all_descriptors (struct usb_function*) ; 

__attribute__((used)) static void f_midi_unbind(struct usb_configuration *c, struct usb_function *f)
{
	struct usb_composite_dev *cdev = f->config->cdev;
	struct f_midi *midi = func_to_midi(f);
	struct snd_card *card;

	DBG(cdev, "unbind\n");

	/* just to be sure */
	f_midi_disable(f);

	card = midi->card;
	midi->card = NULL;
	if (card)
		snd_card_free_when_closed(card);

	usb_free_all_descriptors(f);
}
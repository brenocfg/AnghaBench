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
struct snd_usb_audio {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_audio_usbbus_read ; 
 int /*<<< orphan*/  proc_audio_usbid_read ; 
 int /*<<< orphan*/  snd_card_ro_proc_new (int /*<<< orphan*/ ,char*,struct snd_usb_audio*,int /*<<< orphan*/ ) ; 

void snd_usb_audio_create_proc(struct snd_usb_audio *chip)
{
	snd_card_ro_proc_new(chip->card, "usbbus", chip,
			     proc_audio_usbbus_read);
	snd_card_ro_proc_new(chip->card, "usbid", chip,
			     proc_audio_usbid_read);
}
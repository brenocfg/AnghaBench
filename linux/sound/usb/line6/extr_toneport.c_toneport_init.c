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
struct usb_line6_toneport {int /*<<< orphan*/  firmware_version; int /*<<< orphan*/  serial_number; int /*<<< orphan*/  type; } ;
struct usb_line6 {int /*<<< orphan*/  card; int /*<<< orphan*/  line6pcm; int /*<<< orphan*/  startup; int /*<<< orphan*/  disconnect; } ;
struct usb_device_id {int /*<<< orphan*/  driver_info; } ;

/* Variables and functions */
 int line6_init_pcm (struct usb_line6*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  line6_read_data (struct usb_line6*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  line6_read_serial_number (struct usb_line6*,int /*<<< orphan*/ *) ; 
 struct usb_line6_toneport* line6_to_toneport (struct usb_line6*) ; 
 int /*<<< orphan*/  line6_toneport_disconnect ; 
 int snd_card_register (int /*<<< orphan*/ ) ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toneport_control_monitor ; 
 int /*<<< orphan*/  toneport_control_source ; 
 scalar_t__ toneport_has_led (struct usb_line6_toneport*) ; 
 scalar_t__ toneport_has_source_select (struct usb_line6_toneport*) ; 
 int toneport_init_leds (struct usb_line6_toneport*) ; 
 int /*<<< orphan*/  toneport_pcm_properties ; 
 int toneport_setup (struct usb_line6_toneport*) ; 
 int /*<<< orphan*/  toneport_startup ; 

__attribute__((used)) static int toneport_init(struct usb_line6 *line6,
			 const struct usb_device_id *id)
{
	int err;
	struct usb_line6_toneport *toneport = line6_to_toneport(line6);

	toneport->type = id->driver_info;

	line6->disconnect = line6_toneport_disconnect;
	line6->startup = toneport_startup;

	/* initialize PCM subsystem: */
	err = line6_init_pcm(line6, &toneport_pcm_properties);
	if (err < 0)
		return err;

	/* register monitor control: */
	err = snd_ctl_add(line6->card,
			  snd_ctl_new1(&toneport_control_monitor,
				       line6->line6pcm));
	if (err < 0)
		return err;

	/* register source select control: */
	if (toneport_has_source_select(toneport)) {
		err =
		    snd_ctl_add(line6->card,
				snd_ctl_new1(&toneport_control_source,
					     line6->line6pcm));
		if (err < 0)
			return err;
	}

	line6_read_serial_number(line6, &toneport->serial_number);
	line6_read_data(line6, 0x80c2, &toneport->firmware_version, 1);

	if (toneport_has_led(toneport)) {
		err = toneport_init_leds(toneport);
		if (err < 0)
			return err;
	}

	err = toneport_setup(toneport);
	if (err)
		return err;

	/* register audio system: */
	return snd_card_register(line6->card);
}
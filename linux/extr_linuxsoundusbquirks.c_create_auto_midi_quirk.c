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
struct usb_interface_descriptor {int bNumEndpoints; } ;
struct usb_interface {struct usb_host_interface* altsetting; } ;
struct usb_host_interface {int dummy; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct usb_driver {int dummy; } ;
struct snd_usb_audio {int /*<<< orphan*/  usb_id; } ;

/* Variables and functions */
 int ENODEV ; 
 int USB_ID_VENDOR (int /*<<< orphan*/ ) ; 
 int create_roland_midi_quirk (struct snd_usb_audio*,struct usb_interface*,struct usb_driver*,struct usb_host_interface*) ; 
 int create_std_midi_quirk (struct snd_usb_audio*,struct usb_interface*,struct usb_driver*,struct usb_host_interface*) ; 
 int create_yamaha_midi_quirk (struct snd_usb_audio*,struct usb_interface*,struct usb_driver*,struct usb_host_interface*) ; 
 struct usb_endpoint_descriptor* get_endpoint (struct usb_host_interface*,int /*<<< orphan*/ ) ; 
 struct usb_interface_descriptor* get_iface_desc (struct usb_host_interface*) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_bulk (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_int (struct usb_endpoint_descriptor*) ; 

__attribute__((used)) static int create_auto_midi_quirk(struct snd_usb_audio *chip,
				  struct usb_interface *iface,
				  struct usb_driver *driver)
{
	struct usb_host_interface *alts;
	struct usb_interface_descriptor *altsd;
	struct usb_endpoint_descriptor *epd;
	int err;

	alts = &iface->altsetting[0];
	altsd = get_iface_desc(alts);

	/* must have at least one bulk/interrupt endpoint for streaming */
	if (altsd->bNumEndpoints < 1)
		return -ENODEV;
	epd = get_endpoint(alts, 0);
	if (!usb_endpoint_xfer_bulk(epd) &&
	    !usb_endpoint_xfer_int(epd))
		return -ENODEV;

	switch (USB_ID_VENDOR(chip->usb_id)) {
	case 0x0499: /* Yamaha */
		err = create_yamaha_midi_quirk(chip, iface, driver, alts);
		if (err != -ENODEV)
			return err;
		break;
	case 0x0582: /* Roland */
		err = create_roland_midi_quirk(chip, iface, driver, alts);
		if (err != -ENODEV)
			return err;
		break;
	}

	return create_std_midi_quirk(chip, iface, driver, alts);
}
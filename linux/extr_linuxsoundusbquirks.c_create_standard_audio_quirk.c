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
struct usb_interface_descriptor {int /*<<< orphan*/  bInterfaceNumber; } ;
struct usb_interface {struct usb_host_interface* altsetting; } ;
struct usb_host_interface {int dummy; } ;
struct usb_driver {int dummy; } ;
struct snd_usb_audio_quirk {int dummy; } ;
struct snd_usb_audio {scalar_t__ usb_id; int tx_length_quirk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ USB_ID (int,int) ; 
 struct usb_interface_descriptor* get_iface_desc (struct usb_host_interface*) ; 
 int snd_usb_parse_audio_interface (struct snd_usb_audio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_audio_err (struct snd_usb_audio*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_standard_audio_quirk(struct snd_usb_audio *chip,
				       struct usb_interface *iface,
				       struct usb_driver *driver,
				       const struct snd_usb_audio_quirk *quirk)
{
	struct usb_host_interface *alts;
	struct usb_interface_descriptor *altsd;
	int err;

	if (chip->usb_id == USB_ID(0x1686, 0x00dd)) /* Zoom R16/24 */
		chip->tx_length_quirk = 1;

	alts = &iface->altsetting[0];
	altsd = get_iface_desc(alts);
	err = snd_usb_parse_audio_interface(chip, altsd->bInterfaceNumber);
	if (err < 0) {
		usb_audio_err(chip, "cannot setup if %d: error %d\n",
			   altsd->bInterfaceNumber, err);
		return err;
	}
	/* reset the current interface */
	usb_set_interface(chip->dev, altsd->bInterfaceNumber, 0);
	return 0;
}
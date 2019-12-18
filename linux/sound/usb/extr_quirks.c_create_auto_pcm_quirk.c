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
struct usb_interface {int num_altsetting; struct usb_host_interface* altsetting; } ;
struct usb_host_interface {int /*<<< orphan*/  extralen; int /*<<< orphan*/  extra; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct usb_driver {int dummy; } ;
struct uac_format_type_i_discrete_descriptor {int bLength; } ;
struct uac1_as_header_descriptor {int bLength; } ;
struct snd_usb_audio {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  UAC_AS_GENERAL ; 
 int /*<<< orphan*/  UAC_FORMAT_TYPE ; 
 int create_standard_audio_quirk (struct snd_usb_audio*,struct usb_interface*,struct usb_driver*,int /*<<< orphan*/ *) ; 
 struct usb_endpoint_descriptor* get_endpoint (struct usb_host_interface*,int /*<<< orphan*/ ) ; 
 struct usb_interface_descriptor* get_iface_desc (struct usb_host_interface*) ; 
 void* snd_usb_find_csint_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_isoc (struct usb_endpoint_descriptor*) ; 

__attribute__((used)) static int create_auto_pcm_quirk(struct snd_usb_audio *chip,
				 struct usb_interface *iface,
				 struct usb_driver *driver)
{
	struct usb_host_interface *alts;
	struct usb_interface_descriptor *altsd;
	struct usb_endpoint_descriptor *epd;
	struct uac1_as_header_descriptor *ashd;
	struct uac_format_type_i_discrete_descriptor *fmtd;

	/*
	 * Most Roland/Yamaha audio streaming interfaces have more or less
	 * standard descriptors, but older devices might lack descriptors, and
	 * future ones might change, so ensure that we fail silently if the
	 * interface doesn't look exactly right.
	 */

	/* must have a non-zero altsetting for streaming */
	if (iface->num_altsetting < 2)
		return -ENODEV;
	alts = &iface->altsetting[1];
	altsd = get_iface_desc(alts);

	/* must have an isochronous endpoint for streaming */
	if (altsd->bNumEndpoints < 1)
		return -ENODEV;
	epd = get_endpoint(alts, 0);
	if (!usb_endpoint_xfer_isoc(epd))
		return -ENODEV;

	/* must have format descriptors */
	ashd = snd_usb_find_csint_desc(alts->extra, alts->extralen, NULL,
				       UAC_AS_GENERAL);
	fmtd = snd_usb_find_csint_desc(alts->extra, alts->extralen, NULL,
				       UAC_FORMAT_TYPE);
	if (!ashd || ashd->bLength < 7 ||
	    !fmtd || fmtd->bLength < 8)
		return -ENODEV;

	return create_standard_audio_quirk(chip, iface, driver, NULL);
}
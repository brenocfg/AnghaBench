#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct usb_interface {struct usb_host_interface* altsetting; } ;
struct usb_host_interface {int dummy; } ;
struct usb_device_id {scalar_t__ driver_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {int /*<<< orphan*/  dev; TYPE_1__ descriptor; } ;
struct snd_usb_audio_quirk {int ifnum; scalar_t__ shares_media_device; } ;
struct snd_usb_audio {size_t index; int /*<<< orphan*/  card; int /*<<< orphan*/  num_interfaces; int /*<<< orphan*/  active; scalar_t__ txfr_quirk; struct usb_host_interface* ctrl_intf; struct usb_interface* pm_intf; int /*<<< orphan*/  shutdown; struct usb_device* dev; } ;
struct TYPE_4__ {int bInterfaceNumber; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENXIO ; 
 int QUIRK_NO_INTERFACE ; 
 int SNDRV_CARDS ; 
 int /*<<< orphan*/  USB_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int USB_ID_PRODUCT (int /*<<< orphan*/ ) ; 
 int USB_ID_VENDOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct snd_usb_audio*) ; 
 scalar_t__* enable ; 
 scalar_t__ get_alias_id (struct usb_device*,int /*<<< orphan*/ *) ; 
 struct snd_usb_audio_quirk* get_alias_quirk (struct usb_device*,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_iface_desc (struct usb_host_interface*) ; 
 int /*<<< orphan*/  ignore_ctl_error ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int* pid ; 
 int /*<<< orphan*/  register_mutex ; 
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ ) ; 
 int snd_card_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_media_device_create (struct snd_usb_audio*,struct usb_interface*) ; 
 int snd_usb_apply_boot_quirk (struct usb_device*,struct usb_interface*,struct snd_usb_audio_quirk const*,int /*<<< orphan*/ ) ; 
 int snd_usb_audio_create (struct usb_interface*,struct usb_device*,int,struct snd_usb_audio_quirk const*,int /*<<< orphan*/ ,struct snd_usb_audio**) ; 
 int snd_usb_create_mixer (struct snd_usb_audio*,int,int /*<<< orphan*/ ) ; 
 int snd_usb_create_quirk (struct snd_usb_audio*,struct usb_interface*,int /*<<< orphan*/ *,struct snd_usb_audio_quirk const*) ; 
 int snd_usb_create_streams (struct snd_usb_audio*,int) ; 
 int /*<<< orphan*/  usb_audio_driver ; 
 struct snd_usb_audio** usb_chip ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct snd_usb_audio*) ; 
 int* vid ; 

__attribute__((used)) static int usb_audio_probe(struct usb_interface *intf,
			   const struct usb_device_id *usb_id)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	const struct snd_usb_audio_quirk *quirk =
		(const struct snd_usb_audio_quirk *)usb_id->driver_info;
	struct snd_usb_audio *chip;
	int i, err;
	struct usb_host_interface *alts;
	int ifnum;
	u32 id;

	alts = &intf->altsetting[0];
	ifnum = get_iface_desc(alts)->bInterfaceNumber;
	id = USB_ID(le16_to_cpu(dev->descriptor.idVendor),
		    le16_to_cpu(dev->descriptor.idProduct));
	if (get_alias_id(dev, &id))
		quirk = get_alias_quirk(dev, id);
	if (quirk && quirk->ifnum >= 0 && ifnum != quirk->ifnum)
		return -ENXIO;

	err = snd_usb_apply_boot_quirk(dev, intf, quirk, id);
	if (err < 0)
		return err;

	/*
	 * found a config.  now register to ALSA
	 */

	/* check whether it's already registered */
	chip = NULL;
	mutex_lock(&register_mutex);
	for (i = 0; i < SNDRV_CARDS; i++) {
		if (usb_chip[i] && usb_chip[i]->dev == dev) {
			if (atomic_read(&usb_chip[i]->shutdown)) {
				dev_err(&dev->dev, "USB device is in the shutdown state, cannot create a card instance\n");
				err = -EIO;
				goto __error;
			}
			chip = usb_chip[i];
			atomic_inc(&chip->active); /* avoid autopm */
			break;
		}
	}
	if (! chip) {
		/* it's a fresh one.
		 * now look for an empty slot and create a new card instance
		 */
		for (i = 0; i < SNDRV_CARDS; i++)
			if (!usb_chip[i] &&
			    (vid[i] == -1 || vid[i] == USB_ID_VENDOR(id)) &&
			    (pid[i] == -1 || pid[i] == USB_ID_PRODUCT(id))) {
				if (enable[i]) {
					err = snd_usb_audio_create(intf, dev, i, quirk,
								   id, &chip);
					if (err < 0)
						goto __error;
					chip->pm_intf = intf;
					break;
				} else if (vid[i] != -1 || pid[i] != -1) {
					dev_info(&dev->dev,
						 "device (%04x:%04x) is disabled\n",
						 USB_ID_VENDOR(id),
						 USB_ID_PRODUCT(id));
					err = -ENOENT;
					goto __error;
				}
			}
		if (!chip) {
			dev_err(&dev->dev, "no available usb audio device\n");
			err = -ENODEV;
			goto __error;
		}
	}
	dev_set_drvdata(&dev->dev, chip);

	/*
	 * For devices with more than one control interface, we assume the
	 * first contains the audio controls. We might need a more specific
	 * check here in the future.
	 */
	if (!chip->ctrl_intf)
		chip->ctrl_intf = alts;

	chip->txfr_quirk = 0;
	err = 1; /* continue */
	if (quirk && quirk->ifnum != QUIRK_NO_INTERFACE) {
		/* need some special handlings */
		err = snd_usb_create_quirk(chip, intf, &usb_audio_driver, quirk);
		if (err < 0)
			goto __error;
	}

	if (err > 0) {
		/* create normal USB audio interfaces */
		err = snd_usb_create_streams(chip, ifnum);
		if (err < 0)
			goto __error;
		err = snd_usb_create_mixer(chip, ifnum, ignore_ctl_error);
		if (err < 0)
			goto __error;
	}

	/* we are allowed to call snd_card_register() many times */
	err = snd_card_register(chip->card);
	if (err < 0)
		goto __error;

	if (quirk && quirk->shares_media_device) {
		/* don't want to fail when snd_media_device_create() fails */
		snd_media_device_create(chip, intf);
	}

	usb_chip[chip->index] = chip;
	chip->num_interfaces++;
	usb_set_intfdata(intf, chip);
	atomic_dec(&chip->active);
	mutex_unlock(&register_mutex);
	return 0;

 __error:
	if (chip) {
		/* chip->active is inside the chip->card object,
		 * decrement before memory is possibly returned.
		 */
		atomic_dec(&chip->active);
		if (!chip->num_interfaces)
			snd_card_free(chip->card);
	}
	mutex_unlock(&register_mutex);
	return err;
}
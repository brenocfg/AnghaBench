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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct snd_usb_audio {struct media_device* media_dev; } ;
struct media_device {int /*<<< orphan*/  devnode; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct media_device*) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  media_device_delete (struct media_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int media_device_register (struct media_device*) ; 
 struct media_device* media_device_usb_allocate (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_devnode_is_registered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_media_mixer_delete (struct snd_usb_audio*) ; 
 int snd_media_mixer_init (struct snd_usb_audio*) ; 

int snd_media_device_create(struct snd_usb_audio *chip,
			struct usb_interface *iface)
{
	struct media_device *mdev;
	struct usb_device *usbdev = interface_to_usbdev(iface);
	int ret = 0;

	/* usb-audio driver is probed for each usb interface, and
	 * there are multiple interfaces per device. Avoid calling
	 * media_device_usb_allocate() each time usb_audio_probe()
	 * is called. Do it only once.
	 */
	if (chip->media_dev) {
		mdev = chip->media_dev;
		goto snd_mixer_init;
	}

	mdev = media_device_usb_allocate(usbdev, KBUILD_MODNAME, THIS_MODULE);
	if (IS_ERR(mdev))
		return -ENOMEM;

	/* save media device - avoid lookups */
	chip->media_dev = mdev;

snd_mixer_init:
	/* Create media entities for mixer and control dev */
	ret = snd_media_mixer_init(chip);
	/* media_device might be registered, print error and continue */
	if (ret)
		dev_err(&usbdev->dev,
			"Couldn't create media mixer entities. Error: %d\n",
			ret);

	if (!media_devnode_is_registered(mdev->devnode)) {
		/* dont'register if snd_media_mixer_init() failed */
		if (ret)
			goto create_fail;

		/* register media_device */
		ret = media_device_register(mdev);
create_fail:
		if (ret) {
			snd_media_mixer_delete(chip);
			media_device_delete(mdev, KBUILD_MODNAME, THIS_MODULE);
			/* clear saved media_dev */
			chip->media_dev = NULL;
			dev_err(&usbdev->dev,
				"Couldn't register media device. Error: %d\n",
				ret);
			return ret;
		}
	}

	return ret;
}
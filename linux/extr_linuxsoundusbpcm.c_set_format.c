#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface_descriptor {int /*<<< orphan*/  bAlternateSetting; } ;
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct usb_host_interface {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct snd_usb_substream {int interface; struct audioformat* cur_audiofmt; TYPE_1__* stream; int /*<<< orphan*/  data_endpoint; int /*<<< orphan*/  direction; scalar_t__ altset_idx; struct usb_device* dev; } ;
struct audioformat {int iface; int /*<<< orphan*/  endpoint; scalar_t__ altset_idx; int /*<<< orphan*/  altsetting; } ;
struct TYPE_5__ {int /*<<< orphan*/  keep_iface; } ;
struct TYPE_4__ {TYPE_2__* chip; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  SND_USB_ENDPOINT_TYPE_DATA ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int) ; 
 struct usb_interface_descriptor* get_iface_desc (struct usb_host_interface*) ; 
 int set_sync_endpoint (struct snd_usb_substream*,struct audioformat*,struct usb_device*,struct usb_host_interface*,struct usb_interface_descriptor*) ; 
 int /*<<< orphan*/  snd_usb_add_endpoint (TYPE_2__*,struct usb_host_interface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_usb_init_pitch (TYPE_2__*,int,struct usb_host_interface*,struct audioformat*) ; 
 int snd_usb_select_mode_quirk (struct snd_usb_substream*,struct audioformat*) ; 
 int /*<<< orphan*/  snd_usb_set_format_quirk (struct snd_usb_substream*,struct audioformat*) ; 
 int /*<<< orphan*/  snd_usb_set_interface_quirk (struct usb_device*) ; 
 struct usb_host_interface* usb_altnum_to_altsetting (struct usb_interface*,int /*<<< orphan*/ ) ; 
 struct usb_interface* usb_ifnum_to_if (struct usb_device*,int) ; 
 int usb_set_interface (struct usb_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_format(struct snd_usb_substream *subs, struct audioformat *fmt)
{
	struct usb_device *dev = subs->dev;
	struct usb_host_interface *alts;
	struct usb_interface_descriptor *altsd;
	struct usb_interface *iface;
	int err;

	iface = usb_ifnum_to_if(dev, fmt->iface);
	if (WARN_ON(!iface))
		return -EINVAL;
	alts = usb_altnum_to_altsetting(iface, fmt->altsetting);
	altsd = get_iface_desc(alts);
	if (WARN_ON(altsd->bAlternateSetting != fmt->altsetting))
		return -EINVAL;

	if (fmt == subs->cur_audiofmt)
		return 0;

	/* close the old interface */
	if (subs->interface >= 0 && subs->interface != fmt->iface) {
		if (!subs->stream->chip->keep_iface) {
			err = usb_set_interface(subs->dev, subs->interface, 0);
			if (err < 0) {
				dev_err(&dev->dev,
					"%d:%d: return to setting 0 failed (%d)\n",
					fmt->iface, fmt->altsetting, err);
				return -EIO;
			}
		}
		subs->interface = -1;
		subs->altset_idx = 0;
	}

	/* set interface */
	if (iface->cur_altsetting != alts) {
		err = snd_usb_select_mode_quirk(subs, fmt);
		if (err < 0)
			return -EIO;

		err = usb_set_interface(dev, fmt->iface, fmt->altsetting);
		if (err < 0) {
			dev_err(&dev->dev,
				"%d:%d: usb_set_interface failed (%d)\n",
				fmt->iface, fmt->altsetting, err);
			return -EIO;
		}
		dev_dbg(&dev->dev, "setting usb interface %d:%d\n",
			fmt->iface, fmt->altsetting);
		snd_usb_set_interface_quirk(dev);
	}

	subs->interface = fmt->iface;
	subs->altset_idx = fmt->altset_idx;
	subs->data_endpoint = snd_usb_add_endpoint(subs->stream->chip,
						   alts, fmt->endpoint, subs->direction,
						   SND_USB_ENDPOINT_TYPE_DATA);

	if (!subs->data_endpoint)
		return -EINVAL;

	err = set_sync_endpoint(subs, fmt, dev, alts, altsd);
	if (err < 0)
		return err;

	err = snd_usb_init_pitch(subs->stream->chip, fmt->iface, alts, fmt);
	if (err < 0)
		return err;

	subs->cur_audiofmt = fmt;

	snd_usb_set_format_quirk(subs, fmt);

	return 0;
}
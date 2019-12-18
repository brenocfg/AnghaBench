#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface_descriptor {int bNumEndpoints; } ;
struct usb_host_interface {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct snd_usb_substream {scalar_t__ direction; int /*<<< orphan*/ * sync_endpoint; TYPE_2__* data_endpoint; TYPE_1__* stream; } ;
struct audioformat {unsigned int ep_attr; int /*<<< orphan*/  altsetting; int /*<<< orphan*/  iface; } ;
struct TYPE_6__ {int bmAttributes; scalar_t__ bLength; int bSynchAddress; unsigned int bEndpointAddress; } ;
struct TYPE_5__ {int /*<<< orphan*/ * sync_master; } ;
struct TYPE_4__ {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SND_USB_ENDPOINT_TYPE_DATA ; 
 int /*<<< orphan*/  SND_USB_ENDPOINT_TYPE_SYNC ; 
 int USB_DIR_IN ; 
 scalar_t__ USB_DT_ENDPOINT_AUDIO_SIZE ; 
 unsigned int USB_ENDPOINT_SYNCTYPE ; 
 unsigned int USB_ENDPOINT_SYNC_ADAPTIVE ; 
 unsigned int USB_ENDPOINT_SYNC_ASYNC ; 
 unsigned int USB_ENDPOINT_SYNC_NONE ; 
 unsigned int USB_ENDPOINT_SYNC_SYNC ; 
 int USB_ENDPOINT_USAGE_IMPLICIT_FB ; 
 int USB_ENDPOINT_USAGE_MASK ; 
 int USB_ENDPOINT_XFERTYPE_MASK ; 
 int USB_ENDPOINT_XFER_ISOC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,int) ; 
 TYPE_3__* get_endpoint (struct usb_host_interface*,int) ; 
 int set_sync_ep_implicit_fb_quirk (struct snd_usb_substream*,struct usb_device*,struct usb_interface_descriptor*,unsigned int) ; 
 int /*<<< orphan*/ * snd_usb_add_endpoint (int /*<<< orphan*/ ,struct usb_host_interface*,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_sync_endpoint(struct snd_usb_substream *subs,
			     struct audioformat *fmt,
			     struct usb_device *dev,
			     struct usb_host_interface *alts,
			     struct usb_interface_descriptor *altsd)
{
	int is_playback = subs->direction == SNDRV_PCM_STREAM_PLAYBACK;
	unsigned int ep, attr;
	bool implicit_fb;
	int err;

	/* we need a sync pipe in async OUT or adaptive IN mode */
	/* check the number of EP, since some devices have broken
	 * descriptors which fool us.  if it has only one EP,
	 * assume it as adaptive-out or sync-in.
	 */
	attr = fmt->ep_attr & USB_ENDPOINT_SYNCTYPE;

	if ((is_playback && (attr != USB_ENDPOINT_SYNC_ASYNC)) ||
		(!is_playback && (attr != USB_ENDPOINT_SYNC_ADAPTIVE))) {

		/*
		 * In these modes the notion of sync_endpoint is irrelevant.
		 * Reset pointers to avoid using stale data from previously
		 * used settings, e.g. when configuration and endpoints were
		 * changed
		 */

		subs->sync_endpoint = NULL;
		subs->data_endpoint->sync_master = NULL;
	}

	err = set_sync_ep_implicit_fb_quirk(subs, dev, altsd, attr);
	if (err < 0)
		return err;

	/* endpoint set by quirk */
	if (err > 0)
		return 0;

	if (altsd->bNumEndpoints < 2)
		return 0;

	if ((is_playback && (attr == USB_ENDPOINT_SYNC_SYNC ||
			     attr == USB_ENDPOINT_SYNC_ADAPTIVE)) ||
	    (!is_playback && attr != USB_ENDPOINT_SYNC_ADAPTIVE))
		return 0;

	/*
	 * In case of illegal SYNC_NONE for OUT endpoint, we keep going to see
	 * if we don't find a sync endpoint, as on M-Audio Transit. In case of
	 * error fall back to SYNC mode and don't create sync endpoint
	 */

	/* check sync-pipe endpoint */
	/* ... and check descriptor size before accessing bSynchAddress
	   because there is a version of the SB Audigy 2 NX firmware lacking
	   the audio fields in the endpoint descriptors */
	if ((get_endpoint(alts, 1)->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) != USB_ENDPOINT_XFER_ISOC ||
	    (get_endpoint(alts, 1)->bLength >= USB_DT_ENDPOINT_AUDIO_SIZE &&
	     get_endpoint(alts, 1)->bSynchAddress != 0)) {
		dev_err(&dev->dev,
			"%d:%d : invalid sync pipe. bmAttributes %02x, bLength %d, bSynchAddress %02x\n",
			   fmt->iface, fmt->altsetting,
			   get_endpoint(alts, 1)->bmAttributes,
			   get_endpoint(alts, 1)->bLength,
			   get_endpoint(alts, 1)->bSynchAddress);
		if (is_playback && attr == USB_ENDPOINT_SYNC_NONE)
			return 0;
		return -EINVAL;
	}
	ep = get_endpoint(alts, 1)->bEndpointAddress;
	if (get_endpoint(alts, 0)->bLength >= USB_DT_ENDPOINT_AUDIO_SIZE &&
	    get_endpoint(alts, 0)->bSynchAddress != 0 &&
	    ((is_playback && ep != (unsigned int)(get_endpoint(alts, 0)->bSynchAddress | USB_DIR_IN)) ||
	     (!is_playback && ep != (unsigned int)(get_endpoint(alts, 0)->bSynchAddress & ~USB_DIR_IN)))) {
		dev_err(&dev->dev,
			"%d:%d : invalid sync pipe. is_playback %d, ep %02x, bSynchAddress %02x\n",
			   fmt->iface, fmt->altsetting,
			   is_playback, ep, get_endpoint(alts, 0)->bSynchAddress);
		if (is_playback && attr == USB_ENDPOINT_SYNC_NONE)
			return 0;
		return -EINVAL;
	}

	implicit_fb = (get_endpoint(alts, 1)->bmAttributes & USB_ENDPOINT_USAGE_MASK)
			== USB_ENDPOINT_USAGE_IMPLICIT_FB;

	subs->sync_endpoint = snd_usb_add_endpoint(subs->stream->chip,
						   alts, ep, !subs->direction,
						   implicit_fb ?
							SND_USB_ENDPOINT_TYPE_DATA :
							SND_USB_ENDPOINT_TYPE_SYNC);
	if (!subs->sync_endpoint) {
		if (is_playback && attr == USB_ENDPOINT_SYNC_NONE)
			return 0;
		return -EINVAL;
	}

	subs->data_endpoint->sync_master = subs->sync_endpoint;

	return 0;
}
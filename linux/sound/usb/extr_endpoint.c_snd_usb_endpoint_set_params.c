#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_usb_endpoint {scalar_t__ use_count; int fill_max; int type; int /*<<< orphan*/  nurbs; int /*<<< orphan*/  ep_num; TYPE_1__* chip; scalar_t__ phase; int /*<<< orphan*/  freqshift; int /*<<< orphan*/  freqn; int /*<<< orphan*/  freqm; int /*<<< orphan*/  maxpacksize; int /*<<< orphan*/  datainterval; } ;
struct audioformat {int attributes; int /*<<< orphan*/  maxpacksize; int /*<<< orphan*/  datainterval; } ;
typedef  int /*<<< orphan*/  snd_pcm_format_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  INT_MIN ; 
#define  SND_USB_ENDPOINT_TYPE_DATA 129 
#define  SND_USB_ENDPOINT_TYPE_SYNC 128 
 int UAC_EP_CS_ATTR_FILL_MAX ; 
 scalar_t__ USB_SPEED_FULL ; 
 int data_ep_set_params (struct snd_usb_endpoint*,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,struct audioformat*,struct snd_usb_endpoint*) ; 
 int /*<<< orphan*/  get_usb_full_speed_rate (unsigned int) ; 
 int /*<<< orphan*/  get_usb_high_speed_rate (unsigned int) ; 
 int /*<<< orphan*/  release_urbs (struct snd_usb_endpoint*,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_usb_get_speed (int /*<<< orphan*/ ) ; 
 int sync_ep_set_params (struct snd_usb_endpoint*) ; 
 int /*<<< orphan*/  usb_audio_dbg (TYPE_1__*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_audio_warn (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

int snd_usb_endpoint_set_params(struct snd_usb_endpoint *ep,
				snd_pcm_format_t pcm_format,
				unsigned int channels,
				unsigned int period_bytes,
				unsigned int period_frames,
				unsigned int buffer_periods,
				unsigned int rate,
				struct audioformat *fmt,
				struct snd_usb_endpoint *sync_ep)
{
	int err;

	if (ep->use_count != 0) {
		usb_audio_warn(ep->chip,
			 "Unable to change format on ep #%x: already in use\n",
			 ep->ep_num);
		return -EBUSY;
	}

	/* release old buffers, if any */
	release_urbs(ep, 0);

	ep->datainterval = fmt->datainterval;
	ep->maxpacksize = fmt->maxpacksize;
	ep->fill_max = !!(fmt->attributes & UAC_EP_CS_ATTR_FILL_MAX);

	if (snd_usb_get_speed(ep->chip->dev) == USB_SPEED_FULL)
		ep->freqn = get_usb_full_speed_rate(rate);
	else
		ep->freqn = get_usb_high_speed_rate(rate);

	/* calculate the frequency in 16.16 format */
	ep->freqm = ep->freqn;
	ep->freqshift = INT_MIN;

	ep->phase = 0;

	switch (ep->type) {
	case  SND_USB_ENDPOINT_TYPE_DATA:
		err = data_ep_set_params(ep, pcm_format, channels,
					 period_bytes, period_frames,
					 buffer_periods, fmt, sync_ep);
		break;
	case  SND_USB_ENDPOINT_TYPE_SYNC:
		err = sync_ep_set_params(ep);
		break;
	default:
		err = -EINVAL;
	}

	usb_audio_dbg(ep->chip,
		"Setting params for ep #%x (type %d, %d urbs), ret=%d\n",
		ep->ep_num, ep->type, ep->nurbs, err);

	return err;
}
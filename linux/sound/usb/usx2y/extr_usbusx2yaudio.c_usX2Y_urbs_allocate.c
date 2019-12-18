#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_device {int dummy; } ;
struct urb {unsigned int pipe; int interval; int /*<<< orphan*/  complete; struct snd_usX2Y_substream* context; int /*<<< orphan*/  number_of_packets; struct usb_device* dev; int /*<<< orphan*/ * transfer_buffer; } ;
struct snd_usX2Y_substream {int /*<<< orphan*/  maxpacksize; struct urb** urb; int /*<<< orphan*/ * tmpbuf; int /*<<< orphan*/  endpoint; TYPE_1__* usX2Y; } ;
struct TYPE_2__ {struct usb_device* dev; struct snd_usX2Y_substream** subs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NRURBS ; 
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  i_usX2Y_subs_startup ; 
 int /*<<< orphan*/ * kcalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmalloc_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_of_packs () ; 
 int /*<<< orphan*/  usX2Y_urbs_release (struct snd_usX2Y_substream*) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_maxpacket (struct usb_device*,unsigned int,int) ; 
 unsigned int usb_rcvisocpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndisocpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usX2Y_urbs_allocate(struct snd_usX2Y_substream *subs)
{
	int i;
	unsigned int pipe;
	int is_playback = subs == subs->usX2Y->subs[SNDRV_PCM_STREAM_PLAYBACK];
	struct usb_device *dev = subs->usX2Y->dev;

	pipe = is_playback ? usb_sndisocpipe(dev, subs->endpoint) :
			usb_rcvisocpipe(dev, subs->endpoint);
	subs->maxpacksize = usb_maxpacket(dev, pipe, is_playback);
	if (!subs->maxpacksize)
		return -EINVAL;

	if (is_playback && NULL == subs->tmpbuf) {	/* allocate a temporary buffer for playback */
		subs->tmpbuf = kcalloc(nr_of_packs(), subs->maxpacksize, GFP_KERNEL);
		if (!subs->tmpbuf)
			return -ENOMEM;
	}
	/* allocate and initialize data urbs */
	for (i = 0; i < NRURBS; i++) {
		struct urb **purb = subs->urb + i;
		if (*purb) {
			usb_kill_urb(*purb);
			continue;
		}
		*purb = usb_alloc_urb(nr_of_packs(), GFP_KERNEL);
		if (NULL == *purb) {
			usX2Y_urbs_release(subs);
			return -ENOMEM;
		}
		if (!is_playback && !(*purb)->transfer_buffer) {
			/* allocate a capture buffer per urb */
			(*purb)->transfer_buffer =
				kmalloc_array(subs->maxpacksize,
					      nr_of_packs(), GFP_KERNEL);
			if (NULL == (*purb)->transfer_buffer) {
				usX2Y_urbs_release(subs);
				return -ENOMEM;
			}
		}
		(*purb)->dev = dev;
		(*purb)->pipe = pipe;
		(*purb)->number_of_packets = nr_of_packs();
		(*purb)->context = subs;
		(*purb)->interval = 1;
		(*purb)->complete = i_usX2Y_subs_startup;
	}
	return 0;
}
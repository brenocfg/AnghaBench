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
struct usb_line6 {int /*<<< orphan*/  card; int /*<<< orphan*/  ifcdev; int /*<<< orphan*/  usbdev; struct snd_line6_pcm* line6pcm; TYPE_1__* properties; } ;
struct snd_pcm {int /*<<< orphan*/  private_free; struct snd_line6_pcm* private_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct snd_line6_pcm {int* volume_playback; int volume_monitor; struct usb_line6* line6; void* max_packet_size_out; void* max_packet_size_in; int /*<<< orphan*/  impulse_period; TYPE_3__ in; TYPE_2__ out; struct line6_pcm_properties* properties; struct snd_pcm* pcm; int /*<<< orphan*/  state_mutex; } ;
struct line6_pcm_properties {int dummy; } ;
struct TYPE_4__ {unsigned int ep_audio_r; unsigned int ep_audio_w; int capabilities; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LINE6_CAP_PCM ; 
 int /*<<< orphan*/  LINE6_IMPULSE_DEFAULT_PERIOD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct snd_line6_pcm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line6_cleanup_pcm ; 
 int /*<<< orphan*/ * line6_controls ; 
 int line6_create_audio_in_urbs (struct snd_line6_pcm*) ; 
 int line6_create_audio_out_urbs (struct snd_line6_pcm*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_line6_pcm*) ; 
 int snd_line6_new_pcm (struct usb_line6*,struct snd_pcm**) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* usb_maxpacket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  usb_sndisocpipe (int /*<<< orphan*/ ,unsigned int) ; 

int line6_init_pcm(struct usb_line6 *line6,
		   struct line6_pcm_properties *properties)
{
	int i, err;
	unsigned ep_read = line6->properties->ep_audio_r;
	unsigned ep_write = line6->properties->ep_audio_w;
	struct snd_pcm *pcm;
	struct snd_line6_pcm *line6pcm;

	if (!(line6->properties->capabilities & LINE6_CAP_PCM))
		return 0;	/* skip PCM initialization and report success */

	err = snd_line6_new_pcm(line6, &pcm);
	if (err < 0)
		return err;

	line6pcm = kzalloc(sizeof(*line6pcm), GFP_KERNEL);
	if (!line6pcm)
		return -ENOMEM;

	mutex_init(&line6pcm->state_mutex);
	line6pcm->pcm = pcm;
	line6pcm->properties = properties;
	line6pcm->volume_playback[0] = line6pcm->volume_playback[1] = 255;
	line6pcm->volume_monitor = 255;
	line6pcm->line6 = line6;

	spin_lock_init(&line6pcm->out.lock);
	spin_lock_init(&line6pcm->in.lock);
	line6pcm->impulse_period = LINE6_IMPULSE_DEFAULT_PERIOD;

	line6->line6pcm = line6pcm;

	pcm->private_data = line6pcm;
	pcm->private_free = line6_cleanup_pcm;

	line6pcm->max_packet_size_in =
		usb_maxpacket(line6->usbdev,
			usb_rcvisocpipe(line6->usbdev, ep_read), 0);
	line6pcm->max_packet_size_out =
		usb_maxpacket(line6->usbdev,
			usb_sndisocpipe(line6->usbdev, ep_write), 1);
	if (!line6pcm->max_packet_size_in || !line6pcm->max_packet_size_out) {
		dev_err(line6pcm->line6->ifcdev,
			"cannot get proper max packet size\n");
		return -EINVAL;
	}

	err = line6_create_audio_out_urbs(line6pcm);
	if (err < 0)
		return err;

	err = line6_create_audio_in_urbs(line6pcm);
	if (err < 0)
		return err;

	/* mixer: */
	for (i = 0; i < ARRAY_SIZE(line6_controls); i++) {
		err = snd_ctl_add(line6->card,
				  snd_ctl_new1(&line6_controls[i], line6pcm));
		if (err < 0)
			return err;
	}

	return 0;
}
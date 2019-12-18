#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct usb_mixer_interface {int /*<<< orphan*/  rc_buffer; TYPE_5__* rc_setup_packet; TYPE_2__* chip; int /*<<< orphan*/ * rc_urb; int /*<<< orphan*/  rc_waitq; TYPE_4__* rc_cfg; } ;
struct TYPE_7__ {int /*<<< orphan*/  poll; int /*<<< orphan*/  read; } ;
struct snd_hwdep {int exclusive; TYPE_1__ ops; struct usb_mixer_interface* private_data; int /*<<< orphan*/  iface; int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int bRequestType; void* wLength; void* wIndex; void* wValue; int /*<<< orphan*/  bRequest; } ;
struct TYPE_10__ {scalar_t__ usb_id; int packet_length; } ;
struct TYPE_9__ {char* shortname; } ;
struct TYPE_8__ {scalar_t__ usb_id; int /*<<< orphan*/  dev; TYPE_3__* card; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_HWDEP_IFACE_SB_RC ; 
 int /*<<< orphan*/  UAC_GET_MEM ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 TYPE_5__* kmalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_4__* rc_configs ; 
 int snd_hwdep_new (TYPE_3__*,char*,int /*<<< orphan*/ ,struct snd_hwdep**) ; 
 int /*<<< orphan*/  snd_usb_sbrc_hwdep_poll ; 
 int /*<<< orphan*/  snd_usb_sbrc_hwdep_read ; 
 int /*<<< orphan*/  snd_usb_soundblaster_remote_complete ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/ * usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_control_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct usb_mixer_interface*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_usb_soundblaster_remote_init(struct usb_mixer_interface *mixer)
{
	struct snd_hwdep *hwdep;
	int err, len, i;

	for (i = 0; i < ARRAY_SIZE(rc_configs); ++i)
		if (rc_configs[i].usb_id == mixer->chip->usb_id)
			break;
	if (i >= ARRAY_SIZE(rc_configs))
		return 0;
	mixer->rc_cfg = &rc_configs[i];

	len = mixer->rc_cfg->packet_length;

	init_waitqueue_head(&mixer->rc_waitq);
	err = snd_hwdep_new(mixer->chip->card, "SB remote control", 0, &hwdep);
	if (err < 0)
		return err;
	snprintf(hwdep->name, sizeof(hwdep->name),
		 "%s remote control", mixer->chip->card->shortname);
	hwdep->iface = SNDRV_HWDEP_IFACE_SB_RC;
	hwdep->private_data = mixer;
	hwdep->ops.read = snd_usb_sbrc_hwdep_read;
	hwdep->ops.poll = snd_usb_sbrc_hwdep_poll;
	hwdep->exclusive = 1;

	mixer->rc_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!mixer->rc_urb)
		return -ENOMEM;
	mixer->rc_setup_packet = kmalloc(sizeof(*mixer->rc_setup_packet), GFP_KERNEL);
	if (!mixer->rc_setup_packet) {
		usb_free_urb(mixer->rc_urb);
		mixer->rc_urb = NULL;
		return -ENOMEM;
	}
	mixer->rc_setup_packet->bRequestType =
		USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE;
	mixer->rc_setup_packet->bRequest = UAC_GET_MEM;
	mixer->rc_setup_packet->wValue = cpu_to_le16(0);
	mixer->rc_setup_packet->wIndex = cpu_to_le16(0);
	mixer->rc_setup_packet->wLength = cpu_to_le16(len);
	usb_fill_control_urb(mixer->rc_urb, mixer->chip->dev,
			     usb_rcvctrlpipe(mixer->chip->dev, 0),
			     (u8*)mixer->rc_setup_packet, mixer->rc_buffer, len,
			     snd_usb_soundblaster_remote_complete, mixer);
	return 0;
}
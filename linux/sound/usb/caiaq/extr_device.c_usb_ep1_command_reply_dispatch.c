#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct urb {unsigned char* transfer_buffer; int actual_length; int /*<<< orphan*/  status; struct snd_usb_caiaqdev* context; TYPE_1__* dev; } ;
struct TYPE_7__ {scalar_t__ actual_length; } ;
struct TYPE_6__ {int /*<<< orphan*/  usb_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  data_alignment; int /*<<< orphan*/  num_midi_out; int /*<<< orphan*/  num_midi_in; int /*<<< orphan*/  num_analog_audio_out; int /*<<< orphan*/  num_analog_audio_in; int /*<<< orphan*/  fw_version; } ;
struct snd_usb_caiaqdev {unsigned char audio_parm_answer; TYPE_3__ ep1_in_urb; int /*<<< orphan*/  ep1_wait_queue; TYPE_4__* control_state; TYPE_2__ chip; int /*<<< orphan*/  spec_received; TYPE_4__ spec; } ;
struct device {int dummy; } ;
struct caiaq_device_spec {int dummy; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
#define  EP1_CMD_AUDIO_PARAMS 133 
#define  EP1_CMD_GET_DEVICE_INFO 132 
#define  EP1_CMD_MIDI_READ 131 
#define  EP1_CMD_READ_ANALOG 130 
#define  EP1_CMD_READ_ERP 129 
#define  EP1_CMD_READ_IO 128 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  USB_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_PID_AUDIO8DJ ; 
 int /*<<< orphan*/  USB_VID_NATIVEINSTRUMENTS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_usb_caiaq_input_dispatch (struct snd_usb_caiaqdev*,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_usb_caiaq_midi_handle_input (struct snd_usb_caiaqdev*,unsigned char,unsigned char*,unsigned char) ; 
 int usb_submit_urb (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_ep1_command_reply_dispatch (struct urb* urb)
{
	int ret;
	struct device *dev = &urb->dev->dev;
	struct snd_usb_caiaqdev *cdev = urb->context;
	unsigned char *buf = urb->transfer_buffer;

	if (urb->status || !cdev) {
		dev_warn(dev, "received EP1 urb->status = %i\n", urb->status);
		return;
	}

	switch(buf[0]) {
	case EP1_CMD_GET_DEVICE_INFO:
	 	memcpy(&cdev->spec, buf+1, sizeof(struct caiaq_device_spec));
		cdev->spec.fw_version = le16_to_cpu(cdev->spec.fw_version);
		dev_dbg(dev, "device spec (firmware %d): audio: %d in, %d out, "
			"MIDI: %d in, %d out, data alignment %d\n",
			cdev->spec.fw_version,
			cdev->spec.num_analog_audio_in,
			cdev->spec.num_analog_audio_out,
			cdev->spec.num_midi_in,
			cdev->spec.num_midi_out,
			cdev->spec.data_alignment);

		cdev->spec_received++;
		wake_up(&cdev->ep1_wait_queue);
		break;
	case EP1_CMD_AUDIO_PARAMS:
		cdev->audio_parm_answer = buf[1];
		wake_up(&cdev->ep1_wait_queue);
		break;
	case EP1_CMD_MIDI_READ:
		snd_usb_caiaq_midi_handle_input(cdev, buf[1], buf + 3, buf[2]);
		break;
	case EP1_CMD_READ_IO:
		if (cdev->chip.usb_id ==
			USB_ID(USB_VID_NATIVEINSTRUMENTS, USB_PID_AUDIO8DJ)) {
			if (urb->actual_length > sizeof(cdev->control_state))
				urb->actual_length = sizeof(cdev->control_state);
			memcpy(cdev->control_state, buf + 1, urb->actual_length);
			wake_up(&cdev->ep1_wait_queue);
			break;
		}
#ifdef CONFIG_SND_USB_CAIAQ_INPUT
		/* fall through */
	case EP1_CMD_READ_ERP:
	case EP1_CMD_READ_ANALOG:
		snd_usb_caiaq_input_dispatch(cdev, buf, urb->actual_length);
#endif
		break;
	}

	cdev->ep1_in_urb.actual_length = 0;
	ret = usb_submit_urb(&cdev->ep1_in_urb, GFP_ATOMIC);
	if (ret < 0)
		dev_err(dev, "unable to submit urb. OOM!?\n");
}
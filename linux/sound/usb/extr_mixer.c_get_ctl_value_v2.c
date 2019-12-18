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
struct TYPE_4__ {int id; TYPE_1__* mixer; } ;
struct usb_mixer_elem_info {int /*<<< orphan*/  val_type; TYPE_2__ head; } ;
struct snd_usb_audio {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_3__ {struct snd_usb_audio* chip; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  UAC2_CS_CUR ; 
 int /*<<< orphan*/  UAC2_CS_RANGE ; 
#define  UAC_GET_CUR 131 
#define  UAC_GET_MAX 130 
#define  UAC_GET_MIN 129 
#define  UAC_GET_RES 128 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int convert_signed_value (struct usb_mixer_elem_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_usb_combine_bytes (unsigned char*,int) ; 
 int snd_usb_ctl_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,unsigned char*,int) ; 
 int snd_usb_ctrl_intf (struct snd_usb_audio*) ; 
 scalar_t__ snd_usb_lock_shutdown (struct snd_usb_audio*) ; 
 int /*<<< orphan*/  snd_usb_unlock_shutdown (struct snd_usb_audio*) ; 
 int uac2_ctl_value_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_audio_err (struct snd_usb_audio*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_ctl_value_v2(struct usb_mixer_elem_info *cval, int request,
			    int validx, int *value_ret)
{
	struct snd_usb_audio *chip = cval->head.mixer->chip;
	/* enough space for one range */
	unsigned char buf[sizeof(__u16) + 3 * sizeof(__u32)];
	unsigned char *val;
	int idx = 0, ret, val_size, size;
	__u8 bRequest;

	val_size = uac2_ctl_value_size(cval->val_type);

	if (request == UAC_GET_CUR) {
		bRequest = UAC2_CS_CUR;
		size = val_size;
	} else {
		bRequest = UAC2_CS_RANGE;
		size = sizeof(__u16) + 3 * val_size;
	}

	memset(buf, 0, sizeof(buf));

	ret = snd_usb_lock_shutdown(chip) ? -EIO : 0;
	if (ret)
		goto error;

	idx = snd_usb_ctrl_intf(chip) | (cval->head.id << 8);
	ret = snd_usb_ctl_msg(chip->dev, usb_rcvctrlpipe(chip->dev, 0), bRequest,
			      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_DIR_IN,
			      validx, idx, buf, size);
	snd_usb_unlock_shutdown(chip);

	if (ret < 0) {
error:
		usb_audio_err(chip,
			"cannot get ctl value: req = %#x, wValue = %#x, wIndex = %#x, type = %d\n",
			request, validx, idx, cval->val_type);
		return ret;
	}

	/* FIXME: how should we handle multiple triplets here? */

	switch (request) {
	case UAC_GET_CUR:
		val = buf;
		break;
	case UAC_GET_MIN:
		val = buf + sizeof(__u16);
		break;
	case UAC_GET_MAX:
		val = buf + sizeof(__u16) + val_size;
		break;
	case UAC_GET_RES:
		val = buf + sizeof(__u16) + val_size * 2;
		break;
	default:
		return -EINVAL;
	}

	*value_ret = convert_signed_value(cval,
					  snd_usb_combine_bytes(val, val_size));

	return 0;
}
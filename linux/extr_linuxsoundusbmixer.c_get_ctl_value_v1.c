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
struct TYPE_3__ {struct snd_usb_audio* chip; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int USB_DIR_IN ; 
 int /*<<< orphan*/  USB_MIXER_S16 ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int convert_signed_value (struct usb_mixer_elem_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_usb_combine_bytes (unsigned char*,int) ; 
 int snd_usb_ctl_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,unsigned char*,int) ; 
 int snd_usb_ctrl_intf (struct snd_usb_audio*) ; 
 int snd_usb_lock_shutdown (struct snd_usb_audio*) ; 
 int /*<<< orphan*/  snd_usb_unlock_shutdown (struct snd_usb_audio*) ; 
 int /*<<< orphan*/  usb_audio_dbg (struct snd_usb_audio*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_ctl_value_v1(struct usb_mixer_elem_info *cval, int request,
			    int validx, int *value_ret)
{
	struct snd_usb_audio *chip = cval->head.mixer->chip;
	unsigned char buf[2];
	int val_len = cval->val_type >= USB_MIXER_S16 ? 2 : 1;
	int timeout = 10;
	int idx = 0, err;

	err = snd_usb_lock_shutdown(chip);
	if (err < 0)
		return -EIO;

	while (timeout-- > 0) {
		idx = snd_usb_ctrl_intf(chip) | (cval->head.id << 8);
		err = snd_usb_ctl_msg(chip->dev, usb_rcvctrlpipe(chip->dev, 0), request,
				      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_DIR_IN,
				      validx, idx, buf, val_len);
		if (err >= val_len) {
			*value_ret = convert_signed_value(cval, snd_usb_combine_bytes(buf, val_len));
			err = 0;
			goto out;
		} else if (err == -ETIMEDOUT) {
			goto out;
		}
	}
	usb_audio_dbg(chip,
		"cannot get ctl value: req = %#x, wValue = %#x, wIndex = %#x, type = %d\n",
		request, validx, idx, cval->val_type);
	err = -EINVAL;

 out:
	snd_usb_unlock_shutdown(chip);
	return err;
}
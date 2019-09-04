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
typedef  int /*<<< orphan*/  uac3_conn ;
typedef  int /*<<< orphan*/  uac2_conn ;
struct TYPE_6__ {int id; TYPE_1__* mixer; } ;
struct usb_mixer_elem_info {int control; int /*<<< orphan*/  val_type; TYPE_2__ head; } ;
struct uac3_insertion_ctl_blk {int /*<<< orphan*/  bmConInserted; int /*<<< orphan*/  bNrChannels; } ;
struct uac2_connectors_ctl_blk {int /*<<< orphan*/  bmConInserted; int /*<<< orphan*/  bNrChannels; } ;
struct snd_usb_audio {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {struct usb_mixer_elem_info* private_data; } ;
struct TYPE_7__ {int* value; } ;
struct TYPE_8__ {TYPE_3__ integer; } ;
struct snd_ctl_elem_value {TYPE_4__ value; } ;
struct TYPE_5__ {scalar_t__ protocol; struct snd_usb_audio* chip; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  UAC2_CS_CUR ; 
 int /*<<< orphan*/  UAC_GET_CUR ; 
 scalar_t__ UAC_VERSION_2 ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_CLASS ; 
 int snd_usb_ctl_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,struct uac3_insertion_ctl_blk*,int) ; 
 int snd_usb_ctrl_intf (struct snd_usb_audio*) ; 
 scalar_t__ snd_usb_lock_shutdown (struct snd_usb_audio*) ; 
 int /*<<< orphan*/  snd_usb_unlock_shutdown (struct snd_usb_audio*) ; 
 int /*<<< orphan*/  usb_audio_err (struct snd_usb_audio*,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mixer_ctl_connector_get(struct snd_kcontrol *kcontrol,
				   struct snd_ctl_elem_value *ucontrol)
{
	struct usb_mixer_elem_info *cval = kcontrol->private_data;
	struct snd_usb_audio *chip = cval->head.mixer->chip;
	int idx = 0, validx, ret, val;

	validx = cval->control << 8 | 0;

	ret = snd_usb_lock_shutdown(chip) ? -EIO : 0;
	if (ret)
		goto error;

	idx = snd_usb_ctrl_intf(chip) | (cval->head.id << 8);
	if (cval->head.mixer->protocol == UAC_VERSION_2) {
		struct uac2_connectors_ctl_blk uac2_conn;

		ret = snd_usb_ctl_msg(chip->dev, usb_rcvctrlpipe(chip->dev, 0), UAC2_CS_CUR,
				      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_DIR_IN,
				      validx, idx, &uac2_conn, sizeof(uac2_conn));
		val = !!uac2_conn.bNrChannels;
	} else { /* UAC_VERSION_3 */
		struct uac3_insertion_ctl_blk uac3_conn;

		ret = snd_usb_ctl_msg(chip->dev, usb_rcvctrlpipe(chip->dev, 0), UAC2_CS_CUR,
				      USB_RECIP_INTERFACE | USB_TYPE_CLASS | USB_DIR_IN,
				      validx, idx, &uac3_conn, sizeof(uac3_conn));
		val = !!uac3_conn.bmConInserted;
	}

	snd_usb_unlock_shutdown(chip);

	if (ret < 0) {
error:
		usb_audio_err(chip,
			"cannot get connectors status: req = %#x, wValue = %#x, wIndex = %#x, type = %d\n",
			UAC_GET_CUR, validx, idx, cval->val_type);
		return ret;
	}

	ucontrol->value.integer.value[0] = val;
	return 0;
}
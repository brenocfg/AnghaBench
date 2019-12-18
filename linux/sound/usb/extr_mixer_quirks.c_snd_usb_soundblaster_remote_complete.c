#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct usb_mixer_interface {int* rc_buffer; int rc_code; int /*<<< orphan*/  rc_waitq; struct rc_config* rc_cfg; } ;
struct urb {scalar_t__ status; scalar_t__ actual_length; struct usb_mixer_interface* context; } ;
struct rc_config {scalar_t__ min_packet_length; size_t offset; int length; int mute_code; int /*<<< orphan*/  mute_mixer_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_usb_mixer_notify_id (struct usb_mixer_interface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void snd_usb_soundblaster_remote_complete(struct urb *urb)
{
	struct usb_mixer_interface *mixer = urb->context;
	const struct rc_config *rc = mixer->rc_cfg;
	u32 code;

	if (urb->status < 0 || urb->actual_length < rc->min_packet_length)
		return;

	code = mixer->rc_buffer[rc->offset];
	if (rc->length == 2)
		code |= mixer->rc_buffer[rc->offset + 1] << 8;

	/* the Mute button actually changes the mixer control */
	if (code == rc->mute_code)
		snd_usb_mixer_notify_id(mixer, rc->mute_mixer_id);
	mixer->rc_code = code;
	wmb();
	wake_up(&mixer->rc_waitq);
}
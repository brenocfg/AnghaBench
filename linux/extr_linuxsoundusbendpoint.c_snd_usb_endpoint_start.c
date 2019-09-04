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
struct urb {int /*<<< orphan*/  context; } ;
struct snd_usb_endpoint {int use_count; unsigned int nurbs; scalar_t__ flags; scalar_t__ active_mask; TYPE_1__* chip; int /*<<< orphan*/  pipe; struct snd_urb_ctx* urb; int /*<<< orphan*/  ready_playback_urbs; scalar_t__ phase; scalar_t__ unlink_mask; } ;
struct snd_urb_ctx {struct urb* urb; int /*<<< orphan*/  ready_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  shutdown; } ;

/* Variables and functions */
 int EBADFD ; 
 int EPIPE ; 
 unsigned int EP_FLAG_RUNNING ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,scalar_t__*) ; 
 int /*<<< orphan*/  deactivate_urbs (struct snd_usb_endpoint*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_inbound_urb (struct snd_usb_endpoint*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_outbound_urb (struct snd_usb_endpoint*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (unsigned int,scalar_t__*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 scalar_t__ snd_usb_endpoint_implicit_feedback_sink (struct snd_usb_endpoint*) ; 
 int /*<<< orphan*/  snd_usb_endpoint_start_quirk (struct snd_usb_endpoint*) ; 
 int /*<<< orphan*/  usb_audio_err (TYPE_1__*,char*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_error_string (int) ; 
 scalar_t__ usb_pipeout (int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

int snd_usb_endpoint_start(struct snd_usb_endpoint *ep)
{
	int err;
	unsigned int i;

	if (atomic_read(&ep->chip->shutdown))
		return -EBADFD;

	/* already running? */
	if (++ep->use_count != 1)
		return 0;

	/* just to be sure */
	deactivate_urbs(ep, false);

	ep->active_mask = 0;
	ep->unlink_mask = 0;
	ep->phase = 0;

	snd_usb_endpoint_start_quirk(ep);

	/*
	 * If this endpoint has a data endpoint as implicit feedback source,
	 * don't start the urbs here. Instead, mark them all as available,
	 * wait for the record urbs to return and queue the playback urbs
	 * from that context.
	 */

	set_bit(EP_FLAG_RUNNING, &ep->flags);

	if (snd_usb_endpoint_implicit_feedback_sink(ep)) {
		for (i = 0; i < ep->nurbs; i++) {
			struct snd_urb_ctx *ctx = ep->urb + i;
			list_add_tail(&ctx->ready_list, &ep->ready_playback_urbs);
		}

		return 0;
	}

	for (i = 0; i < ep->nurbs; i++) {
		struct urb *urb = ep->urb[i].urb;

		if (snd_BUG_ON(!urb))
			goto __error;

		if (usb_pipeout(ep->pipe)) {
			prepare_outbound_urb(ep, urb->context);
		} else {
			prepare_inbound_urb(ep, urb->context);
		}

		err = usb_submit_urb(urb, GFP_ATOMIC);
		if (err < 0) {
			usb_audio_err(ep->chip,
				"cannot submit urb %d, error %d: %s\n",
				i, err, usb_error_string(err));
			goto __error;
		}
		set_bit(i, &ep->active_mask);
	}

	return 0;

__error:
	clear_bit(EP_FLAG_RUNNING, &ep->flags);
	ep->use_count--;
	deactivate_urbs(ep, false);
	return -EPIPE;
}
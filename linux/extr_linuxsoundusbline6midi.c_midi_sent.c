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
struct usb_line6 {TYPE_1__* line6midi; } ;
struct urb {int status; int /*<<< orphan*/  transfer_buffer; scalar_t__ context; } ;
struct TYPE_2__ {int num_active_send_urbs; int /*<<< orphan*/  lock; int /*<<< orphan*/  send_wait; int /*<<< orphan*/  substream_transmit; } ;

/* Variables and functions */
 int ESHUTDOWN ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line6_midi_transmit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void midi_sent(struct urb *urb)
{
	unsigned long flags;
	int status;
	int num;
	struct usb_line6 *line6 = (struct usb_line6 *)urb->context;

	status = urb->status;
	kfree(urb->transfer_buffer);
	usb_free_urb(urb);

	if (status == -ESHUTDOWN)
		return;

	spin_lock_irqsave(&line6->line6midi->lock, flags);
	num = --line6->line6midi->num_active_send_urbs;

	if (num == 0) {
		line6_midi_transmit(line6->line6midi->substream_transmit);
		num = line6->line6midi->num_active_send_urbs;
	}

	if (num == 0)
		wake_up(&line6->line6midi->send_wait);

	spin_unlock_irqrestore(&line6->line6midi->lock, flags);
}
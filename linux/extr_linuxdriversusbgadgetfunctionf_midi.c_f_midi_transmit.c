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
struct usb_ep {int /*<<< orphan*/  enabled; } ;
struct f_midi {int /*<<< orphan*/  transmit_lock; struct usb_ep* in_ep; } ;

/* Variables and functions */
 int f_midi_do_transmit (struct f_midi*,struct usb_ep*) ; 
 int /*<<< orphan*/  f_midi_drop_out_substreams (struct f_midi*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void f_midi_transmit(struct f_midi *midi)
{
	struct usb_ep *ep = midi->in_ep;
	int ret;
	unsigned long flags;

	/* We only care about USB requests if IN endpoint is enabled */
	if (!ep || !ep->enabled)
		goto drop_out;

	spin_lock_irqsave(&midi->transmit_lock, flags);

	do {
		ret = f_midi_do_transmit(midi, ep);
		if (ret < 0) {
			spin_unlock_irqrestore(&midi->transmit_lock, flags);
			goto drop_out;
		}
	} while (ret);

	spin_unlock_irqrestore(&midi->transmit_lock, flags);

	return;

drop_out:
	f_midi_drop_out_substreams(midi);
}
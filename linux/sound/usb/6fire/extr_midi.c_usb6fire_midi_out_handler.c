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
struct urb {int transfer_buffer_length; TYPE_1__* dev; struct midi_runtime* context; } ;
struct midi_runtime {int* out_buffer; int /*<<< orphan*/  out_lock; int /*<<< orphan*/ * out; int /*<<< orphan*/  out_serial; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MIDI_BUFSIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int snd_rawmidi_transmit (int /*<<< orphan*/ *,int*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb6fire_midi_out_handler(struct urb *urb)
{
	struct midi_runtime *rt = urb->context;
	int ret;
	unsigned long flags;

	spin_lock_irqsave(&rt->out_lock, flags);

	if (rt->out) {
		ret = snd_rawmidi_transmit(rt->out, rt->out_buffer + 4,
				MIDI_BUFSIZE - 4);
		if (ret > 0) { /* more data available, send next packet */
			rt->out_buffer[1] = ret + 2;
			rt->out_buffer[3] = rt->out_serial++;
			urb->transfer_buffer_length = ret + 4;

			ret = usb_submit_urb(urb, GFP_ATOMIC);
			if (ret < 0)
				dev_err(&urb->dev->dev,
					"midi out urb submit failed: %d\n",
					ret);
		} else /* no more data to transmit */
			rt->out = NULL;
	}
	spin_unlock_irqrestore(&rt->out_lock, flags);
}
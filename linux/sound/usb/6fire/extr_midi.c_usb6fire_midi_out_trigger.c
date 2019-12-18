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
struct urb {TYPE_2__* dev; scalar_t__ transfer_buffer_length; } ;
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct midi_runtime {int /*<<< orphan*/  out_lock; struct snd_rawmidi_substream* out; int /*<<< orphan*/  out_serial; scalar_t__* out_buffer; struct urb out_urb; } ;
typedef  scalar_t__ __s8 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct midi_runtime* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MIDI_BUFSIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ snd_rawmidi_transmit (struct snd_rawmidi_substream*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb6fire_midi_out_trigger(
		struct snd_rawmidi_substream *alsa_sub, int up)
{
	struct midi_runtime *rt = alsa_sub->rmidi->private_data;
	struct urb *urb = &rt->out_urb;
	__s8 ret;
	unsigned long flags;

	spin_lock_irqsave(&rt->out_lock, flags);
	if (up) { /* start transfer */
		if (rt->out) { /* we are already transmitting so just return */
			spin_unlock_irqrestore(&rt->out_lock, flags);
			return;
		}

		ret = snd_rawmidi_transmit(alsa_sub, rt->out_buffer + 4,
				MIDI_BUFSIZE - 4);
		if (ret > 0) {
			rt->out_buffer[1] = ret + 2;
			rt->out_buffer[3] = rt->out_serial++;
			urb->transfer_buffer_length = ret + 4;

			ret = usb_submit_urb(urb, GFP_ATOMIC);
			if (ret < 0)
				dev_err(&urb->dev->dev,
					"midi out urb submit failed: %d\n",
					ret);
			else
				rt->out = alsa_sub;
		}
	} else if (rt->out == alsa_sub)
		rt->out = NULL;
	spin_unlock_irqrestore(&rt->out_lock, flags);
}
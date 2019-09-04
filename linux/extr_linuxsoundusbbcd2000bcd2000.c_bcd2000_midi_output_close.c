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
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct bcd2000 {scalar_t__ midi_out_active; int /*<<< orphan*/  midi_out_urb; } ;
struct TYPE_2__ {struct bcd2000* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcd2000_midi_output_close(struct snd_rawmidi_substream *substream)
{
	struct bcd2000 *bcd2k = substream->rmidi->private_data;

	if (bcd2k->midi_out_active) {
		usb_kill_urb(bcd2k->midi_out_urb);
		bcd2k->midi_out_active = 0;
	}

	return 0;
}
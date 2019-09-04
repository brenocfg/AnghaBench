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
struct snd_usb_midi {int /*<<< orphan*/  input_triggered; } ;
struct snd_rawmidi_substream {int /*<<< orphan*/  number; TYPE_1__* rmidi; } ;
struct TYPE_2__ {struct snd_usb_midi* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_usbmidi_input_trigger(struct snd_rawmidi_substream *substream,
				      int up)
{
	struct snd_usb_midi *umidi = substream->rmidi->private_data;

	if (up)
		set_bit(substream->number, &umidi->input_triggered);
	else
		clear_bit(substream->number, &umidi->input_triggered);
}
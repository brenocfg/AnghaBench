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
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_ep {struct f_midi* driver_data; } ;
struct snd_rawmidi_substream {int dummy; } ;
struct f_midi {int /*<<< orphan*/  out_triggered; struct snd_rawmidi_substream** out_substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_rawmidi_receive (struct snd_rawmidi_substream*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void f_midi_read_data(struct usb_ep *ep, int cable,
			     uint8_t *data, int length)
{
	struct f_midi *midi = ep->driver_data;
	struct snd_rawmidi_substream *substream = midi->out_substream[cable];

	if (!substream)
		/* Nobody is listening - throw it on the floor. */
		return;

	if (!test_bit(cable, &midi->out_triggered))
		return;

	snd_rawmidi_receive(substream, data, length);
}
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
struct TYPE_2__ {scalar_t__ substream_receive; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_rawmidi_receive (scalar_t__,unsigned char*,int) ; 

void line6_midi_receive(struct usb_line6 *line6, unsigned char *data,
			int length)
{
	if (line6->line6midi->substream_receive)
		snd_rawmidi_receive(line6->line6midi->substream_receive,
				    data, length);
}
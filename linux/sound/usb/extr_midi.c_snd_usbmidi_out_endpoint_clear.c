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
struct snd_usb_midi_out_endpoint {TYPE_1__* urbs; int /*<<< orphan*/  max_transfer; int /*<<< orphan*/  umidi; } ;
struct TYPE_2__ {int /*<<< orphan*/ * urb; } ;

/* Variables and functions */
 unsigned int OUTPUT_URBS ; 
 int /*<<< orphan*/  free_urb_and_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_usbmidi_out_endpoint_clear(struct snd_usb_midi_out_endpoint *ep)
{
	unsigned int i;

	for (i = 0; i < OUTPUT_URBS; ++i)
		if (ep->urbs[i].urb) {
			free_urb_and_buffer(ep->umidi, ep->urbs[i].urb,
					    ep->max_transfer);
			ep->urbs[i].urb = NULL;
		}
}
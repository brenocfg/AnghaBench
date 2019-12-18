#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usbmidi_out_port {int active; TYPE_3__* ep; } ;
struct snd_rawmidi_substream {TYPE_1__* runtime; } ;
struct TYPE_6__ {int /*<<< orphan*/  tasklet; TYPE_2__* umidi; } ;
struct TYPE_5__ {scalar_t__ disconnected; } ;
struct TYPE_4__ {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_rawmidi_proceed (struct snd_rawmidi_substream*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_usbmidi_output_trigger(struct snd_rawmidi_substream *substream,
				       int up)
{
	struct usbmidi_out_port *port =
		(struct usbmidi_out_port *)substream->runtime->private_data;

	port->active = up;
	if (up) {
		if (port->ep->umidi->disconnected) {
			/* gobble up remaining bytes to prevent wait in
			 * snd_rawmidi_drain_output */
			snd_rawmidi_proceed(substream);
			return;
		}
		tasklet_schedule(&port->ep->tasklet);
	}
}
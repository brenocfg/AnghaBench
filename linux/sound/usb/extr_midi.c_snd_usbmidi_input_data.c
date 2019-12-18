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
typedef  int /*<<< orphan*/  uint8_t ;
struct usbmidi_in_port {TYPE_3__* substream; } ;
struct snd_usb_midi_in_endpoint {TYPE_2__* umidi; struct usbmidi_in_port* ports; } ;
struct TYPE_6__ {int /*<<< orphan*/  number; } ;
struct TYPE_5__ {int /*<<< orphan*/  input_triggered; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_usbmidi_input_data(struct snd_usb_midi_in_endpoint *ep,
				   int portidx, uint8_t *data, int length)
{
	struct usbmidi_in_port *port = &ep->ports[portidx];

	if (!port->substream) {
		dev_dbg(&ep->umidi->dev->dev, "unexpected port %d!\n", portidx);
		return;
	}
	if (!test_bit(port->substream->number, &ep->umidi->input_triggered))
		return;
	snd_rawmidi_receive(port->substream, data, length);
}
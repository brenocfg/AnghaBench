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
struct snd_rawmidi_substream {int dummy; } ;
struct snd_fw_async_midi_port {int /*<<< orphan*/  work; struct snd_rawmidi_substream* substream; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
snd_fw_async_midi_port_run(struct snd_fw_async_midi_port *port,
			   struct snd_rawmidi_substream *substream)
{
	if (!port->error) {
		port->substream = substream;
		schedule_work(&port->work);
	}
}
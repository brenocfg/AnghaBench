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
struct snd_tscm {int /*<<< orphan*/ * out_ports; } ;
struct snd_rawmidi_substream {size_t number; TYPE_1__* rmidi; } ;
struct TYPE_2__ {struct snd_tscm* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_fw_async_midi_port_finish (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void midi_playback_drain(struct snd_rawmidi_substream *substream)
{
	struct snd_tscm *tscm = substream->rmidi->private_data;

	snd_fw_async_midi_port_finish(&tscm->out_ports[substream->number]);
}
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
struct snd_emux_port {int volume_atten; TYPE_1__* oss_arg; scalar_t__ drum_flags; int /*<<< orphan*/  port_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_passing; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_DRUM_FLAGS ; 
 int /*<<< orphan*/  SNDRV_EMUX_PORT_MODE_OSS_MIDI ; 
 int /*<<< orphan*/  SNDRV_EMUX_PORT_MODE_OSS_SYNTH ; 
 int /*<<< orphan*/  SNDRV_SEQ_OSS_PROCESS_EVENTS ; 
 int /*<<< orphan*/  SNDRV_SEQ_OSS_PROCESS_KEYPRESS ; 

__attribute__((used)) static void
reset_port_mode(struct snd_emux_port *port, int midi_mode)
{
	if (midi_mode) {
		port->port_mode = SNDRV_EMUX_PORT_MODE_OSS_MIDI;
		port->drum_flags = DEFAULT_DRUM_FLAGS;
		port->volume_atten = 0;
		port->oss_arg->event_passing = SNDRV_SEQ_OSS_PROCESS_KEYPRESS;
	} else {
		port->port_mode = SNDRV_EMUX_PORT_MODE_OSS_SYNTH;
		port->drum_flags = 0;
		port->volume_atten = 32;
		port->oss_arg->event_passing = SNDRV_SEQ_OSS_PROCESS_EVENTS;
	}
}
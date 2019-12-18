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
struct snd_midi_channel {unsigned short midi_program; int* control; } ;
struct TYPE_2__ {int max_channels; struct snd_midi_channel* channels; } ;
struct snd_emux_port {scalar_t__ port_mode; TYPE_1__ chset; } ;
struct snd_emux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMUX_FX_COARSE_SAMPLE_START ; 
 int /*<<< orphan*/  EMUX_FX_FLAG_SET ; 
 int /*<<< orphan*/  EMUX_FX_SAMPLE_START ; 
 size_t MIDI_CTL_MSB_PAN ; 
 scalar_t__ SNDRV_EMUX_PORT_MODE_OSS_SYNTH ; 
 int /*<<< orphan*/  SNDRV_EMUX_UPDATE_PAN ; 
 int _GUS_NUMVOICES ; 
#define  _GUS_RAMPMODE 138 
#define  _GUS_RAMPOFF 137 
#define  _GUS_RAMPON 136 
#define  _GUS_RAMPRANGE 135 
#define  _GUS_RAMPRATE 134 
#define  _GUS_VOICEBALA 133 
#define  _GUS_VOICESAMPLE 132 
#define  _GUS_VOICEVOL 131 
#define  _GUS_VOICEVOL2 130 
#define  _GUS_VOICE_POS 129 
#define  _GUS_VOLUME_SCALE 128 
 int /*<<< orphan*/  snd_emux_send_effect (struct snd_emux_port*,struct snd_midi_channel*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emux_update_channel (struct snd_emux_port*,struct snd_midi_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gusspec_control(struct snd_emux *emu, struct snd_emux_port *port, int cmd,
		unsigned char *event, int atomic, int hop)
{
	int voice;
	unsigned short p1;
	int plong;
	struct snd_midi_channel *chan;

	if (port->port_mode != SNDRV_EMUX_PORT_MODE_OSS_SYNTH)
		return;
	if (cmd == _GUS_NUMVOICES)
		return;
	voice = event[3];
	if (voice < 0 || voice >= port->chset.max_channels)
		return;

	chan = &port->chset.channels[voice];

	p1 = *(unsigned short *) &event[4];
	plong = *(int*) &event[4];

	switch (cmd) {
	case _GUS_VOICESAMPLE:
		chan->midi_program = p1;
		return;

	case _GUS_VOICEBALA:
		/* 0 to 15 --> 0 to 127 */
		chan->control[MIDI_CTL_MSB_PAN] = (int)p1 << 3;
		snd_emux_update_channel(port, chan, SNDRV_EMUX_UPDATE_PAN);
		return;

	case _GUS_VOICEVOL:
	case _GUS_VOICEVOL2:
		/* not supported yet */
		return;

	case _GUS_RAMPRANGE:
	case _GUS_RAMPRATE:
	case _GUS_RAMPMODE:
	case _GUS_RAMPON:
	case _GUS_RAMPOFF:
		/* volume ramping not supported */
		return;

	case _GUS_VOLUME_SCALE:
		return;

	case _GUS_VOICE_POS:
#ifdef SNDRV_EMUX_USE_RAW_EFFECT
		snd_emux_send_effect(port, chan, EMUX_FX_SAMPLE_START,
				     (short)(plong & 0x7fff),
				     EMUX_FX_FLAG_SET);
		snd_emux_send_effect(port, chan, EMUX_FX_COARSE_SAMPLE_START,
				     (plong >> 15) & 0xffff,
				     EMUX_FX_FLAG_SET);
#endif
		return;
	}
}
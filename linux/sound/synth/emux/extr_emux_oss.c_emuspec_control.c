#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_midi_channel {unsigned short midi_pressure; int drum_channel; } ;
struct TYPE_3__ {int max_channels; struct snd_midi_channel* channels; } ;
struct snd_emux_port {short volume_atten; unsigned int drum_flags; short* ctrls; TYPE_1__ chset; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* oss_ioctl ) (struct snd_emux*,int,unsigned short,short) ;} ;
struct snd_emux {TYPE_2__ ops; int /*<<< orphan*/  sflist; } ;

/* Variables and functions */
 unsigned short EMUX_MD_END ; 
 int /*<<< orphan*/  MIDI_CTL_ALL_NOTES_OFF ; 
 int /*<<< orphan*/  MIDI_CTL_ALL_SOUNDS_OFF ; 
 int SNDRV_EMUX_UPDATE_FM2FRQ2 ; 
 int SNDRV_EMUX_UPDATE_FMMOD ; 
 int /*<<< orphan*/  SNDRV_EMUX_UPDATE_VOLUME ; 
#define  _EMUX_OSS_CHANNEL_MODE 140 
#define  _EMUX_OSS_CHN_PRESSURE 139 
#define  _EMUX_OSS_DEBUG_MODE 138 
#define  _EMUX_OSS_DRUM_CHANNELS 137 
#define  _EMUX_OSS_INITIAL_VOLUME 136 
#define  _EMUX_OSS_MISC_MODE 135 
#define  _EMUX_OSS_NOTEOFF_ALL 134 
#define  _EMUX_OSS_RELEASE_ALL 133 
#define  _EMUX_OSS_REMOVE_LAST_SAMPLES 132 
#define  _EMUX_OSS_RESET_CHANNEL 131 
#define  _EMUX_OSS_SEND_EFFECT 130 
#define  _EMUX_OSS_TERMINATE_ALL 129 
#define  _EMUX_OSS_TERMINATE_CHANNEL 128 
 int /*<<< orphan*/  fake_event (struct snd_emux*,struct snd_emux_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  reset_port_mode (struct snd_emux_port*,unsigned short) ; 
 int /*<<< orphan*/  snd_emux_reset_port (struct snd_emux_port*) ; 
 int /*<<< orphan*/  snd_emux_send_effect_oss (struct snd_emux_port*,struct snd_midi_channel*,unsigned short,short) ; 
 int /*<<< orphan*/  snd_emux_terminate_all (struct snd_emux*) ; 
 int /*<<< orphan*/  snd_emux_update_channel (struct snd_emux_port*,struct snd_midi_channel*,int) ; 
 int /*<<< orphan*/  snd_emux_update_port (struct snd_emux_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soundfont_remove_unlocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_emux*,int,unsigned short,short) ; 

__attribute__((used)) static void
emuspec_control(struct snd_emux *emu, struct snd_emux_port *port, int cmd,
		unsigned char *event, int atomic, int hop)
{
	int voice;
	unsigned short p1;
	short p2;
	int i;
	struct snd_midi_channel *chan;

	voice = event[3];
	if (voice < 0 || voice >= port->chset.max_channels)
		chan = NULL;
	else
		chan = &port->chset.channels[voice];

	p1 = *(unsigned short *) &event[4];
	p2 = *(short *) &event[6];

	switch (cmd) {
#if 0 /* don't do this atomically */
	case _EMUX_OSS_REMOVE_LAST_SAMPLES:
		snd_soundfont_remove_unlocked(emu->sflist);
		break;
#endif
	case _EMUX_OSS_SEND_EFFECT:
		if (chan)
			snd_emux_send_effect_oss(port, chan, p1, p2);
		break;
		
	case _EMUX_OSS_TERMINATE_ALL:
		snd_emux_terminate_all(emu);
		break;

	case _EMUX_OSS_TERMINATE_CHANNEL:
		/*snd_emux_mute_channel(emu, chan);*/
		break;
	case _EMUX_OSS_RESET_CHANNEL:
		/*snd_emux_channel_init(chset, chan);*/
		break;

	case _EMUX_OSS_RELEASE_ALL:
		fake_event(emu, port, voice, MIDI_CTL_ALL_NOTES_OFF, 0, atomic, hop);
		break;
	case _EMUX_OSS_NOTEOFF_ALL:
		fake_event(emu, port, voice, MIDI_CTL_ALL_SOUNDS_OFF, 0, atomic, hop);
		break;

	case _EMUX_OSS_INITIAL_VOLUME:
		if (p2) {
			port->volume_atten = (short)p1;
			snd_emux_update_port(port, SNDRV_EMUX_UPDATE_VOLUME);
		}
		break;

	case _EMUX_OSS_CHN_PRESSURE:
		if (chan) {
			chan->midi_pressure = p1;
			snd_emux_update_channel(port, chan, SNDRV_EMUX_UPDATE_FMMOD|SNDRV_EMUX_UPDATE_FM2FRQ2);
		}
		break;

	case _EMUX_OSS_CHANNEL_MODE:
		reset_port_mode(port, p1);
		snd_emux_reset_port(port);
		break;

	case _EMUX_OSS_DRUM_CHANNELS:
		port->drum_flags = *(unsigned int*)&event[4];
		for (i = 0; i < port->chset.max_channels; i++) {
			chan = &port->chset.channels[i];
			chan->drum_channel = ((port->drum_flags >> i) & 1) ? 1 : 0;
		}
		break;

	case _EMUX_OSS_MISC_MODE:
		if (p1 < EMUX_MD_END)
			port->ctrls[p1] = p2;
		break;
	case _EMUX_OSS_DEBUG_MODE:
		break;

	default:
		if (emu->ops.oss_ioctl)
			emu->ops.oss_ioctl(emu, cmd, p1, p2);
		break;
	}
}
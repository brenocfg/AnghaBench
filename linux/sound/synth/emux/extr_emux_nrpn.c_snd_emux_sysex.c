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
struct snd_midi_channel_set {int dummy; } ;
struct snd_emux_port {struct snd_emux* emu; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sysex ) (struct snd_emux*,unsigned char*,int,int,struct snd_midi_channel_set*) ;} ;
struct snd_emux {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_EMUX_UPDATE_VOLUME ; 
#define  SNDRV_MIDI_SYSEX_GS_MASTER_VOLUME 128 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_emux_update_port (struct snd_emux_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct snd_emux*,unsigned char*,int,int,struct snd_midi_channel_set*) ; 

void
snd_emux_sysex(void *p, unsigned char *buf, int len, int parsed,
	       struct snd_midi_channel_set *chset)
{
	struct snd_emux_port *port;
	struct snd_emux *emu;

	port = p;
	if (snd_BUG_ON(!port || !chset))
		return;
	emu = port->emu;

	switch (parsed) {
	case SNDRV_MIDI_SYSEX_GS_MASTER_VOLUME:
		snd_emux_update_port(port, SNDRV_EMUX_UPDATE_VOLUME);
		break;
	default:
		if (emu->ops.sysex)
			emu->ops.sysex(emu, buf, len, parsed, chset);
		break;
	}
}
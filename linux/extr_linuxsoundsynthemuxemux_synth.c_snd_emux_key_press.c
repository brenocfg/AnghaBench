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
struct snd_midi_channel {int dummy; } ;
struct snd_emux_voice {scalar_t__ state; int key; int velocity; struct snd_midi_channel* chan; } ;
struct snd_emux_port {struct snd_emux* emu; } ;
struct TYPE_2__ {int /*<<< orphan*/  update; } ;
struct snd_emux {int max_voices; int /*<<< orphan*/  voice_lock; struct snd_emux_voice* voices; TYPE_1__ ops; } ;

/* Variables and functions */
 scalar_t__ SNDRV_EMUX_ST_ON ; 
 int /*<<< orphan*/  SNDRV_EMUX_UPDATE_VOLUME ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_voice (struct snd_emux*,struct snd_emux_voice*,int /*<<< orphan*/ ) ; 

void
snd_emux_key_press(void *p, int note, int vel, struct snd_midi_channel *chan)
{
	int ch;
	struct snd_emux *emu;
	struct snd_emux_voice *vp;
	unsigned long flags;
	struct snd_emux_port *port;

	port = p;
	if (snd_BUG_ON(!port || !chan))
		return;

	emu = port->emu;
	if (snd_BUG_ON(!emu || !emu->ops.update))
		return;

	spin_lock_irqsave(&emu->voice_lock, flags);
	for (ch = 0; ch < emu->max_voices; ch++) {
		vp = &emu->voices[ch];
		if (vp->state == SNDRV_EMUX_ST_ON &&
		    vp->chan == chan && vp->key == note) {
			vp->velocity = vel;
			update_voice(emu, vp, SNDRV_EMUX_UPDATE_VOLUME);
		}
	}
	spin_unlock_irqrestore(&emu->voice_lock, flags);
}
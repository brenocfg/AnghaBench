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
struct snd_emux_voice {scalar_t__ state; struct snd_emux_port* port; } ;
struct snd_emux_port {struct snd_emux* emu; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct snd_emux*,int) ;int /*<<< orphan*/  (* free_voice ) (struct snd_emux_voice*) ;int /*<<< orphan*/  terminate; } ;
struct snd_emux {int max_voices; int /*<<< orphan*/  voice_lock; TYPE_1__ ops; struct snd_emux_voice* voices; } ;

/* Variables and functions */
 scalar_t__ SNDRV_EMUX_ST_OFF ; 
 scalar_t__ STATE_IS_PLAYING (scalar_t__) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct snd_emux_voice*) ; 
 int /*<<< orphan*/  stub2 (struct snd_emux*,int) ; 
 int /*<<< orphan*/  terminate_voice (struct snd_emux*,struct snd_emux_voice*,int /*<<< orphan*/ ) ; 

void
snd_emux_sounds_off_all(struct snd_emux_port *port)
{
	int i;
	struct snd_emux *emu;
	struct snd_emux_voice *vp;
	unsigned long flags;

	if (snd_BUG_ON(!port))
		return;
	emu = port->emu;
	if (snd_BUG_ON(!emu || !emu->ops.terminate))
		return;

	spin_lock_irqsave(&emu->voice_lock, flags);
	for (i = 0; i < emu->max_voices; i++) {
		vp = &emu->voices[i];
		if (STATE_IS_PLAYING(vp->state) &&
		    vp->port == port)
			terminate_voice(emu, vp, 0);
		if (vp->state == SNDRV_EMUX_ST_OFF) {
			if (emu->ops.free_voice)
				emu->ops.free_voice(vp);
			if (emu->ops.reset)
				emu->ops.reset(emu, i);
		}
	}
	spin_unlock_irqrestore(&emu->voice_lock, flags);
}
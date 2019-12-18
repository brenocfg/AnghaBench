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
struct snd_emux_voice {int /*<<< orphan*/  state; int /*<<< orphan*/ * block; int /*<<< orphan*/ * zone; int /*<<< orphan*/ * port; int /*<<< orphan*/ * chan; scalar_t__ time; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_voice ) (struct snd_emux_voice*) ;int /*<<< orphan*/  (* terminate ) (struct snd_emux_voice*) ;} ;
struct snd_emux {TYPE_1__ ops; int /*<<< orphan*/  use_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_EMUX_ST_OFF ; 
 int /*<<< orphan*/  stub1 (struct snd_emux_voice*) ; 
 int /*<<< orphan*/  stub2 (struct snd_emux_voice*) ; 

__attribute__((used)) static void
terminate_voice(struct snd_emux *emu, struct snd_emux_voice *vp, int free)
{
	emu->ops.terminate(vp);
	vp->time = emu->use_time++;
	vp->chan = NULL;
	vp->port = NULL;
	vp->zone = NULL;
	vp->block = NULL;
	vp->state = SNDRV_EMUX_ST_OFF;
	if (free && emu->ops.free_voice)
		emu->ops.free_voice(vp);
}
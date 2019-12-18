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
struct TYPE_3__ {int first_audio; } ;
struct snd_pcxhr {int nb_streams_capt; TYPE_2__* capture_pipe; TYPE_1__ playback_pipe; scalar_t__ nb_streams_play; } ;
struct pcxhr_mgr {int num_cards; struct snd_pcxhr** chip; } ;
struct TYPE_4__ {int first_audio; } ;

/* Variables and functions */
 int pcxhr_set_pipe_state (struct pcxhr_mgr*,int,int,int) ; 

__attribute__((used)) static int pcxhr_start_pipes(struct pcxhr_mgr *mgr)
{
	int i, j;
	struct snd_pcxhr *chip;
	int playback_mask = 0;
	int capture_mask = 0;

	/* start all the pipes on the dsp */
	for (i = 0; i < mgr->num_cards; i++) {
		chip = mgr->chip[i];
		if (chip->nb_streams_play)
			playback_mask |= 1 << chip->playback_pipe.first_audio;
		for (j = 0; j < chip->nb_streams_capt; j++)
			capture_mask |= 1 << chip->capture_pipe[j].first_audio;
	}
	return pcxhr_set_pipe_state(mgr, playback_mask, capture_mask, 1);
}
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
struct snd_midi_channel {int number; int gm_rpn_pitch_bend_range; int drum_channel; scalar_t__ gm_rpn_coarse_tuning; scalar_t__ gm_rpn_fine_tuning; int /*<<< orphan*/ * private; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct snd_midi_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_midi_reset_controllers (struct snd_midi_channel*) ; 

__attribute__((used)) static void snd_midi_channel_init(struct snd_midi_channel *p, int n)
{
	if (p == NULL)
		return;

	memset(p, 0, sizeof(struct snd_midi_channel));
	p->private = NULL;
	p->number = n;

	snd_midi_reset_controllers(p);
	p->gm_rpn_pitch_bend_range = 256; /* 2 semitones */
	p->gm_rpn_fine_tuning = 0;
	p->gm_rpn_coarse_tuning = 0;

	if (n == 9)
		p->drum_channel = 1;	/* Default ch 10 as drums */
}
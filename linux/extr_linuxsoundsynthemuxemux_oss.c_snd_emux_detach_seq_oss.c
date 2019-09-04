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
struct snd_emux {int /*<<< orphan*/ * oss_synth; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_device_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
snd_emux_detach_seq_oss(struct snd_emux *emu)
{
	if (emu->oss_synth) {
		snd_device_free(emu->card, emu->oss_synth);
		emu->oss_synth = NULL;
	}
}
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
struct snd_rawmidi {struct snd_emu10k1_midi* private_data; } ;
struct snd_emu10k1_midi {int /*<<< orphan*/ * rmidi; int /*<<< orphan*/ * interrupt; } ;

/* Variables and functions */

__attribute__((used)) static void snd_emu10k1_midi_free(struct snd_rawmidi *rmidi)
{
	struct snd_emu10k1_midi *midi = rmidi->private_data;
	midi->interrupt = NULL;
	midi->rmidi = NULL;
}
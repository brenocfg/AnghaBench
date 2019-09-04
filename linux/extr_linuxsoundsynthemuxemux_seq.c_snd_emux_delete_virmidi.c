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
struct snd_emux {int midi_ports; scalar_t__* vmidi; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int /*<<< orphan*/  snd_device_free (int /*<<< orphan*/ ,scalar_t__) ; 

int snd_emux_delete_virmidi(struct snd_emux *emu)
{
	int i;

	if (!emu->vmidi)
		return 0;

	for (i = 0; i < emu->midi_ports; i++) {
		if (emu->vmidi[i])
			snd_device_free(emu->card, emu->vmidi[i]);
	}
	kfree(emu->vmidi);
	emu->vmidi = NULL;
	return 0;
}
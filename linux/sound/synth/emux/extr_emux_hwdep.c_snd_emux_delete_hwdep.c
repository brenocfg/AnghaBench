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
struct snd_emux {int /*<<< orphan*/ * hwdep; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_device_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
snd_emux_delete_hwdep(struct snd_emux *emu)
{
	if (emu->hwdep) {
		snd_device_free(emu->card, emu->hwdep);
		emu->hwdep = NULL;
	}
}
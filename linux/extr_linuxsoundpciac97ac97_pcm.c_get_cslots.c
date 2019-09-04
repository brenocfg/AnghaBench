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
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int AC97_SLOT_MIC ; 
 int AC97_SLOT_PCM_LEFT ; 
 int AC97_SLOT_PCM_RIGHT ; 
 int /*<<< orphan*/  ac97_is_audio (struct snd_ac97*) ; 

__attribute__((used)) static unsigned short get_cslots(struct snd_ac97 *ac97)
{
	unsigned short slots;

	if (!ac97_is_audio(ac97))
		return 0;
	slots = (1<<AC97_SLOT_PCM_LEFT)|(1<<AC97_SLOT_PCM_RIGHT);
	slots |= (1<<AC97_SLOT_MIC);
	return slots;
}
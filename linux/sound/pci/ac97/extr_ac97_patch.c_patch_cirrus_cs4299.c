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
struct snd_ac97 {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_HAS_PC_BEEP ; 
 int patch_cirrus_spdif (struct snd_ac97*) ; 

__attribute__((used)) static int patch_cirrus_cs4299(struct snd_ac97 * ac97)
{
	/* force the detection of PC Beep */
	ac97->flags |= AC97_HAS_PC_BEEP;
	
	return patch_cirrus_spdif(ac97);
}
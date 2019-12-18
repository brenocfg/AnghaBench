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
struct snd_ac97 {int /*<<< orphan*/  flags; int /*<<< orphan*/ * build_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_HAS_NO_PCM_VOL ; 
 int /*<<< orphan*/  AC97_PCM ; 
 int /*<<< orphan*/  patch_cm9738_ops ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int patch_cm9738(struct snd_ac97 * ac97)
{
	ac97->build_ops = &patch_cm9738_ops;
	/* FIXME: can anyone confirm below? */
	/* CM9738 has no PCM volume although the register reacts */
	ac97->flags |= AC97_HAS_NO_PCM_VOL;
	snd_ac97_write_cache(ac97, AC97_PCM, 0x8000);

	return 0;
}
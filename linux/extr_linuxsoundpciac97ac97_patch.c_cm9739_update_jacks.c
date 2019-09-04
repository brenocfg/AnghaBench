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
 int /*<<< orphan*/  AC97_CM9739_MULTI_CHAN ; 
 scalar_t__ is_shared_clfeout (struct snd_ac97*) ; 
 scalar_t__ is_shared_surrout (struct snd_ac97*) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void cm9739_update_jacks(struct snd_ac97 *ac97)
{
	/* shared Line-In / Surround Out */
	snd_ac97_update_bits(ac97, AC97_CM9739_MULTI_CHAN, 1 << 10,
			     is_shared_surrout(ac97) ? (1 << 10) : 0);
	/* shared Mic In / Center/LFE Out **/
	snd_ac97_update_bits(ac97, AC97_CM9739_MULTI_CHAN, 0x3000,
			     is_shared_clfeout(ac97) ? 0x1000 : 0x2000);
}
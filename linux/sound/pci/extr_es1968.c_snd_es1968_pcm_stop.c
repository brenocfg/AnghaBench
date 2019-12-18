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
struct esschan {scalar_t__ mode; int /*<<< orphan*/ * apu; } ;
struct es1968 {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 scalar_t__ ESM_MODE_CAPTURE ; 
 int /*<<< orphan*/  snd_es1968_trigger_apu (struct es1968*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_es1968_pcm_stop(struct es1968 *chip, struct esschan *es)
{
	spin_lock(&chip->reg_lock);
	snd_es1968_trigger_apu(chip, es->apu[0], 0);
	snd_es1968_trigger_apu(chip, es->apu[1], 0);
	if (es->mode == ESM_MODE_CAPTURE) {
		snd_es1968_trigger_apu(chip, es->apu[2], 0);
		snd_es1968_trigger_apu(chip, es->apu[3], 0);
	}
	spin_unlock(&chip->reg_lock);
}
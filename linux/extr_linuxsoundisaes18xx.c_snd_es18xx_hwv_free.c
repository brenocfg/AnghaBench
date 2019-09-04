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
struct snd_kcontrol {int dummy; } ;
struct snd_es18xx {int /*<<< orphan*/ * hw_switch; int /*<<< orphan*/ * hw_volume; int /*<<< orphan*/ * master_switch; int /*<<< orphan*/ * master_volume; } ;

/* Variables and functions */
 struct snd_es18xx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static void snd_es18xx_hwv_free(struct snd_kcontrol *kcontrol)
{
	struct snd_es18xx *chip = snd_kcontrol_chip(kcontrol);
	chip->master_volume = NULL;
	chip->master_switch = NULL;
	chip->hw_volume = NULL;
	chip->hw_switch = NULL;
}
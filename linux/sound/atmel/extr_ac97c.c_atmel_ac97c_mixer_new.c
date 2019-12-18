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
typedef  int /*<<< orphan*/  template ;
struct snd_ac97_template {struct atmel_ac97c* private_data; } ;
struct atmel_ac97c {int /*<<< orphan*/  ac97; int /*<<< orphan*/  ac97_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct snd_ac97_template*,int /*<<< orphan*/ ,int) ; 
 int snd_ac97_mixer (int /*<<< orphan*/ ,struct snd_ac97_template*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_ac97c_mixer_new(struct atmel_ac97c *chip)
{
	struct snd_ac97_template template;
	memset(&template, 0, sizeof(template));
	template.private_data = chip;
	return snd_ac97_mixer(chip->ac97_bus, &template, &chip->ac97);
}
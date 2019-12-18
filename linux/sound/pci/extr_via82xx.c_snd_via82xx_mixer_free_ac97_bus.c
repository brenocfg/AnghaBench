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
struct via82xx {int /*<<< orphan*/ * ac97_bus; } ;
struct snd_ac97_bus {struct via82xx* private_data; } ;

/* Variables and functions */

__attribute__((used)) static void snd_via82xx_mixer_free_ac97_bus(struct snd_ac97_bus *bus)
{
	struct via82xx *chip = bus->private_data;
	chip->ac97_bus = NULL;
}
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
struct snd_ac97_bus {struct fm801* private_data; } ;
struct fm801 {int /*<<< orphan*/ * ac97_bus; } ;

/* Variables and functions */

__attribute__((used)) static void snd_fm801_mixer_free_ac97_bus(struct snd_ac97_bus *bus)
{
	struct fm801 *chip = bus->private_data;
	chip->ac97_bus = NULL;
}
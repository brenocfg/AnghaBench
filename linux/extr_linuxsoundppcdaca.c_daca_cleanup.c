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
struct snd_pmac {struct pmac_daca* mixer_data; } ;
struct pmac_daca {int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pmac_daca*) ; 
 int /*<<< orphan*/  snd_pmac_keywest_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void daca_cleanup(struct snd_pmac *chip)
{
	struct pmac_daca *mix = chip->mixer_data;
	if (! mix)
		return;
	snd_pmac_keywest_cleanup(&mix->i2c);
	kfree(mix);
	chip->mixer_data = NULL;
}
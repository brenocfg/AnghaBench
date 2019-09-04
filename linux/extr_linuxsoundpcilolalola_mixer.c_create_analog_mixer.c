#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lola {int /*<<< orphan*/  card; TYPE_1__* pin; } ;
struct TYPE_5__ {char* name; int private_value; } ;
struct TYPE_4__ {scalar_t__ num_pins; scalar_t__ num_analog_pins; } ;

/* Variables and functions */
 TYPE_2__ lola_analog_mixer ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (TYPE_2__*,struct lola*) ; 

__attribute__((used)) static int create_analog_mixer(struct lola *chip, int dir, char *name)
{
	if (!chip->pin[dir].num_pins)
		return 0;
	/* no analog volumes on digital only adapters */
	if (chip->pin[dir].num_pins != chip->pin[dir].num_analog_pins)
		return 0;
	lola_analog_mixer.name = name;
	lola_analog_mixer.private_value = dir;
	return snd_ctl_add(chip->card,
			   snd_ctl_new1(&lola_analog_mixer, chip));
}
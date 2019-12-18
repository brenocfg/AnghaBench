#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lola {TYPE_1__* pin; } ;
struct TYPE_4__ {scalar_t__ is_analog; } ;
struct TYPE_3__ {int num_pins; int /*<<< orphan*/  num_analog_pins; TYPE_2__* pins; } ;

/* Variables and functions */
 int lola_init_pin (struct lola*,TYPE_2__*,int,int) ; 

int lola_init_pins(struct lola *chip, int dir, int *nidp)
{
	int i, err, nid;
	nid = *nidp;
	for (i = 0; i < chip->pin[dir].num_pins; i++, nid++) {
		err = lola_init_pin(chip, &chip->pin[dir].pins[i], dir, nid);
		if (err < 0)
			return err;
		if (chip->pin[dir].pins[i].is_analog)
			chip->pin[dir].num_analog_pins++;
	}
	*nidp = nid;
	return 0;
}
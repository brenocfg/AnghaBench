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
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGPIO_MAGICIAN_IN_SEL1 ; 
#define  MAGICIAN_MIC 129 
#define  MAGICIAN_MIC_EXT 128 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int magician_in_sel ; 

__attribute__((used)) static int magician_set_input(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_value *ucontrol)
{
	if (magician_in_sel == ucontrol->value.enumerated.item[0])
		return 0;

	magician_in_sel = ucontrol->value.enumerated.item[0];

	switch (magician_in_sel) {
	case MAGICIAN_MIC:
		gpio_set_value(EGPIO_MAGICIAN_IN_SEL1, 1);
		break;
	case MAGICIAN_MIC_EXT:
		gpio_set_value(EGPIO_MAGICIAN_IN_SEL1, 0);
	}

	return 1;
}
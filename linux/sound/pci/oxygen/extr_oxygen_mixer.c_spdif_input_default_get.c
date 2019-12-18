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
typedef  int u32 ;
struct snd_kcontrol {struct oxygen* private_data; } ;
struct TYPE_3__ {int* status; } ;
struct TYPE_4__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OXYGEN_SPDIF_INPUT_BITS ; 
 int oxygen_read32 (struct oxygen*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spdif_input_default_get(struct snd_kcontrol *ctl,
				   struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	u32 bits;

	bits = oxygen_read32(chip, OXYGEN_SPDIF_INPUT_BITS);
	value->value.iec958.status[0] = bits;
	value->value.iec958.status[1] = bits >> 8;
	value->value.iec958.status[2] = bits >> 16;
	value->value.iec958.status[3] = bits >> 24;
	return 0;
}
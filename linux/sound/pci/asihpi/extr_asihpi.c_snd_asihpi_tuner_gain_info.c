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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_3__ {int min; int max; int step; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int HPI_UNITS_PER_dB ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
 scalar_t__ hpi_tuner_query_gain (int /*<<< orphan*/ ,short,scalar_t__*) ; 

__attribute__((used)) static int snd_asihpi_tuner_gain_info(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_info *uinfo)
{
	u32 h_control = kcontrol->private_value;
	u16 err;
	short idx;
	u16 gain_range[3];

	for (idx = 0; idx < 3; idx++) {
		err = hpi_tuner_query_gain(h_control,
					  idx, &gain_range[idx]);
		if (err != 0)
			return err;
	}

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.integer.min = ((int)gain_range[0]) / HPI_UNITS_PER_dB;
	uinfo->value.integer.max = ((int)gain_range[1]) / HPI_UNITS_PER_dB;
	uinfo->value.integer.step = ((int) gain_range[2]) / HPI_UNITS_PER_dB;
	return 0;
}
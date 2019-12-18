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
struct TYPE_3__ {short min; short max; short step; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 short HPI_UNITS_PER_dB ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
 scalar_t__ hpi_level_query_range (int /*<<< orphan*/ ,short*,short*,short*) ; 

__attribute__((used)) static int snd_asihpi_level_info(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_info *uinfo)
{
	u32 h_control = kcontrol->private_value;
	u16 err;
	short min_gain_mB;
	short max_gain_mB;
	short step_gain_mB;

	err =
	    hpi_level_query_range(h_control, &min_gain_mB,
			       &max_gain_mB, &step_gain_mB);
	if (err) {
		max_gain_mB = 2400;
		min_gain_mB = -1000;
		step_gain_mB = 100;
	}

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.integer.min = min_gain_mB / HPI_UNITS_PER_dB;
	uinfo->value.integer.max = max_gain_mB / HPI_UNITS_PER_dB;
	uinfo->value.integer.step = step_gain_mB / HPI_UNITS_PER_dB;
	return 0;
}
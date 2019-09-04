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
struct TYPE_3__ {short* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int HPI_MAX_CHANNELS ; 
 scalar_t__ hpi_meter_get_peak (int /*<<< orphan*/ ,short*) ; 
 short* log2lin ; 

__attribute__((used)) static int snd_asihpi_meter_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	u32 h_control = kcontrol->private_value;
	short an_gain_mB[HPI_MAX_CHANNELS], i;
	u16 err;

	err = hpi_meter_get_peak(h_control, an_gain_mB);

	for (i = 0; i < HPI_MAX_CHANNELS; i++) {
		if (err) {
			ucontrol->value.integer.value[i] = 0;
		} else if (an_gain_mB[i] >= 0) {
			ucontrol->value.integer.value[i] =
				an_gain_mB[i] << 16;
		} else {
			/* -ve is log value in millibels < -60dB,
			* convert to (roughly!) linear,
			*/
			ucontrol->value.integer.value[i] =
					log2lin[an_gain_mB[i] / -1000];
		}
	}
	return 0;
}
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
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_3__ {short* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int HPI_MAX_CHANNELS ; 
 short HPI_UNITS_PER_dB ; 
 int /*<<< orphan*/  hpi_handle_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_level_get_gain (int /*<<< orphan*/ ,short*) ; 

__attribute__((used)) static int snd_asihpi_level_get(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	u32 h_control = kcontrol->private_value;
	short an_gain_mB[HPI_MAX_CHANNELS];

	hpi_handle_error(hpi_level_get_gain(h_control, an_gain_mB));
	ucontrol->value.integer.value[0] =
	    an_gain_mB[0] / HPI_UNITS_PER_dB;
	ucontrol->value.integer.value[1] =
	    an_gain_mB[1] / HPI_UNITS_PER_dB;

	return 0;
}
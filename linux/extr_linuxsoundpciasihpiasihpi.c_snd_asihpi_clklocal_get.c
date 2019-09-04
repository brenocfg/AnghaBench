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
typedef  int /*<<< orphan*/  u16 ;
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  hpi_sample_clock_get_local_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_asihpi_clklocal_get(struct snd_kcontrol *kcontrol,
				  struct snd_ctl_elem_value *ucontrol)
{
	u32 h_control = kcontrol->private_value;
	u32 rate;
	u16 e;

	e = hpi_sample_clock_get_local_rate(h_control, &rate);
	if (!e)
		ucontrol->value.integer.value[0] = rate;
	else
		ucontrol->value.integer.value[0] = 0;
	return 0;
}
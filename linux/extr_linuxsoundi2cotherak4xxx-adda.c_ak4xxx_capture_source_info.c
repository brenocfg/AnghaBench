#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int /*<<< orphan*/  private_value; } ;
struct snd_ctl_elem_info {int dummy; } ;
struct snd_akm4xxx {TYPE_1__* adc_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  input_names; } ;

/* Variables and functions */
 int AK_GET_SHIFT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 unsigned int ak4xxx_capture_num_inputs (struct snd_akm4xxx*,int) ; 
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,unsigned int,int /*<<< orphan*/ ) ; 
 struct snd_akm4xxx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int ak4xxx_capture_source_info(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_info *uinfo)
{
	struct snd_akm4xxx *ak = snd_kcontrol_chip(kcontrol);
	int mixer_ch = AK_GET_SHIFT(kcontrol->private_value);
	unsigned int num_names;

	num_names = ak4xxx_capture_num_inputs(ak, mixer_ch);
	if (!num_names)
		return -EINVAL;
	return snd_ctl_enum_info(uinfo, 1, num_names,
				 ak->adc_info[mixer_ch].input_names);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct snd_kcontrol {int private_value; } ;
struct snd_ctl_elem_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENUMERATED_CTL_INFO (struct snd_ctl_elem_info*,char const* const*) ; 
#define  HDSPM_c0_Input0 128 

__attribute__((used)) static int snd_hdspm_info_tristate(struct snd_kcontrol *kcontrol,
				       struct snd_ctl_elem_info *uinfo)
{
	u32 regmask = kcontrol->private_value;

	static const char *const texts_spdif[] = { "Optical", "Coaxial", "Internal" };
	static const char *const texts_levels[] = { "Hi Gain", "+4 dBu", "-10 dBV" };

	switch (regmask) {
	case HDSPM_c0_Input0:
		ENUMERATED_CTL_INFO(uinfo, texts_spdif);
		break;
	default:
		ENUMERATED_CTL_INFO(uinfo, texts_levels);
		break;
	}
	return 0;
}
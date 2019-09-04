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
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ dev_flags; } ;
struct snd_ac97 {TYPE_1__ spec; } ;

/* Variables and functions */
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int,char const* const*) ; 
 struct snd_ac97* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int alc655_iec958_route_info(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
	static const char * const texts_655[3] = {
		"PCM", "Analog In", "IEC958 In"
	};
	static const char * const texts_658[4] = {
		"PCM", "Analog1 In", "Analog2 In", "IEC958 In"
	};
	struct snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);

	if (ac97->spec.dev_flags)
		return snd_ctl_enum_info(uinfo, 1, 4, texts_658);
	else
		return snd_ctl_enum_info(uinfo, 1, 3, texts_655);
}
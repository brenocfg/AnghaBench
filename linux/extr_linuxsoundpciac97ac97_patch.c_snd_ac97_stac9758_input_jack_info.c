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
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_info {int dummy; } ;

/* Variables and functions */
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int,char const* const*) ; 

__attribute__((used)) static int snd_ac97_stac9758_input_jack_info(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_info *uinfo)
{
	static const char * const texts[7] = {
		"Mic2 Jack", "Mic1 Jack", "Line In Jack",
		"Front Jack", "Rear Jack", "Center/LFE Jack", "Mute" };

	return snd_ctl_enum_info(uinfo, 1, 7, texts);
}
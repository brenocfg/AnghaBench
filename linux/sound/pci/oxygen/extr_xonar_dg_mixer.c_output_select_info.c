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

__attribute__((used)) static int output_select_info(struct snd_kcontrol *ctl,
			      struct snd_ctl_elem_info *info)
{
	static const char *const names[3] = {
		"Stereo Headphones",
		"Stereo Headphones FP",
		"Multichannel",
	};

	return snd_ctl_enum_info(info, 1, 3, names);
}
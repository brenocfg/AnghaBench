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
struct cmipci {int chip_version; } ;

/* Variables and functions */
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int,char const* const*) ; 
 struct cmipci* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_cmipci_line_in_mode_info(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_info *uinfo)
{
	struct cmipci *cm = snd_kcontrol_chip(kcontrol);
	static const char *const texts[3] = {
		"Line-In", "Rear Output", "Bass Output"
	};

	return snd_ctl_enum_info(uinfo, 1,
				 cm->chip_version >= 39 ? 3 : 2, texts);
}
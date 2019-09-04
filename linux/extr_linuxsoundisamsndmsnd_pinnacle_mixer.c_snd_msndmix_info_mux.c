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
struct snd_msnd {int /*<<< orphan*/  flags; } ;
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_HAVEDIGITAL ; 
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,unsigned int,char const* const*) ; 
 struct snd_msnd* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_msndmix_info_mux(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_info *uinfo)
{
	static const char * const texts[3] = {
		"Analog", "MASS", "SPDIF",
	};
	struct snd_msnd *chip = snd_kcontrol_chip(kcontrol);
	unsigned items = test_bit(F_HAVEDIGITAL, &chip->flags) ? 3 : 2;

	return snd_ctl_enum_info(uinfo, 1, items, texts);
}
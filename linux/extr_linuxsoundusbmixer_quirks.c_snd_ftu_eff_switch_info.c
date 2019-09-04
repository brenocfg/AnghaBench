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
 int /*<<< orphan*/  ARRAY_SIZE (char const* const*) ; 
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int /*<<< orphan*/ ,char const* const*) ; 

__attribute__((used)) static int snd_ftu_eff_switch_info(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_info *uinfo)
{
	static const char *const texts[8] = {
		"Room 1", "Room 2", "Room 3", "Hall 1",
		"Hall 2", "Plate", "Delay", "Echo"
	};

	return snd_ctl_enum_info(uinfo, 1, ARRAY_SIZE(texts), texts);
}
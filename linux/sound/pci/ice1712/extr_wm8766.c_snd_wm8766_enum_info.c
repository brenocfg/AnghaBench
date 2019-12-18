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
struct snd_wm8766 {TYPE_1__* ctl; } ;
struct snd_kcontrol {int private_value; } ;
struct snd_ctl_elem_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  enum_names; int /*<<< orphan*/  max; } ;

/* Variables and functions */
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_wm8766* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_wm8766_enum_info(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_info *uinfo)
{
	struct snd_wm8766 *wm = snd_kcontrol_chip(kcontrol);
	int n = kcontrol->private_value;

	return snd_ctl_enum_info(uinfo, 1, wm->ctl[n].max,
						wm->ctl[n].enum_names);
}
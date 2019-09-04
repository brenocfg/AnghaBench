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
struct snd_kcontrol {scalar_t__ private_value; } ;
struct snd_ctl_elem_info {int dummy; } ;
struct ac97_enum {scalar_t__ shift_l; scalar_t__ shift_r; int /*<<< orphan*/  texts; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_ac97_info_enum_double(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_info *uinfo)
{
	struct ac97_enum *e = (struct ac97_enum *)kcontrol->private_value;
	
	return snd_ctl_enum_info(uinfo, e->shift_l == e->shift_r ? 1 : 2,
				 e->mask, e->texts);
}
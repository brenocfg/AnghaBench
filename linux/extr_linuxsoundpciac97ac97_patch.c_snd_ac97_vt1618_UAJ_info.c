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
struct snd_kcontrol {size_t private_value; } ;
struct snd_ctl_elem_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  items; } ;

/* Variables and functions */
 int snd_ctl_enum_info (struct snd_ctl_elem_info*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* vt1618_uaj ; 

__attribute__((used)) static int snd_ac97_vt1618_UAJ_info(struct snd_kcontrol *kcontrol,
				    struct snd_ctl_elem_info *uinfo)
{
	return snd_ctl_enum_info(uinfo, 1, 4,
				 vt1618_uaj[kcontrol->private_value].items);
}
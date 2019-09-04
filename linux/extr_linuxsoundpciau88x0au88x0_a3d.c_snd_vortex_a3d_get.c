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
struct snd_ctl_elem_value {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
snd_vortex_a3d_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	//a3dsrc_t *a = kcontrol->private_data;
	/* No read yet. Would this be really useable/needed ? */

	return 0;
}
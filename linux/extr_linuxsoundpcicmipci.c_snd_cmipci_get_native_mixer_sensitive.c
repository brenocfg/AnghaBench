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
 int snd_cmipci_get_native_mixer (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int snd_cmipci_get_native_mixer_sensitive(struct snd_kcontrol *kcontrol,
						 struct snd_ctl_elem_value *ucontrol)
{
	//struct cmipci *cm = snd_kcontrol_chip(kcontrol);
	return snd_cmipci_get_native_mixer(kcontrol, ucontrol);
}
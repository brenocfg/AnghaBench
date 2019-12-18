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
struct link_slave {int dummy; } ;

/* Variables and functions */
 int slave_get_val (struct link_slave*,struct snd_ctl_elem_value*) ; 
 struct link_slave* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int slave_get(struct snd_kcontrol *kcontrol,
		     struct snd_ctl_elem_value *ucontrol)
{
	struct link_slave *slave = snd_kcontrol_chip(kcontrol);
	return slave_get_val(slave, ucontrol);
}
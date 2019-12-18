#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_rme9652 {int dummy; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int RME9652_lock_0 ; 
 unsigned int RME9652_lock_1 ; 
 unsigned int RME9652_lock_2 ; 
 int /*<<< orphan*/  RME9652_status_register ; 
 unsigned int RME9652_sync_0 ; 
 unsigned int RME9652_sync_1 ; 
 unsigned int RME9652_sync_2 ; 
 unsigned int rme9652_read (struct snd_rme9652*,int /*<<< orphan*/ ) ; 
 struct snd_rme9652* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_rme9652_get_adat_sync(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_rme9652 *rme9652 = snd_kcontrol_chip(kcontrol);
	unsigned int mask1, mask2, val;
	
	switch (kcontrol->private_value) {
	case 0: mask1 = RME9652_lock_0; mask2 = RME9652_sync_0; break;	
	case 1: mask1 = RME9652_lock_1; mask2 = RME9652_sync_1; break;	
	case 2: mask1 = RME9652_lock_2; mask2 = RME9652_sync_2; break;	
	default: return -EINVAL;
	}
	val = rme9652_read(rme9652, RME9652_status_register);
	ucontrol->value.enumerated.item[0] = (val & mask1) ? 1 : 0;
	ucontrol->value.enumerated.item[0] |= (val & mask2) ? 2 : 0;
	return 0;
}
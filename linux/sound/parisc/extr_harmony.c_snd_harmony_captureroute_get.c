#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int gain; } ;
struct snd_harmony {int /*<<< orphan*/  mixer_lock; TYPE_1__ st; } ;
struct TYPE_5__ {int* item; } ;
struct TYPE_6__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;

/* Variables and functions */
 int HARMONY_GAIN_IS_SHIFT ; 
 struct snd_harmony* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int 
snd_harmony_captureroute_get(struct snd_kcontrol *kc, 
			     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_harmony *h = snd_kcontrol_chip(kc);
	int value;
	
	spin_lock_irq(&h->mixer_lock);

	value = (h->st.gain >> HARMONY_GAIN_IS_SHIFT) & 1;
	ucontrol->value.enumerated.item[0] = value;

	spin_unlock_irq(&h->mixer_lock);

	return 0;
}
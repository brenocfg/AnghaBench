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
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int* item; } ;
struct TYPE_3__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct hdspm {int texts_autosync_items; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int hdspm_pref_sync_ref (struct hdspm*) ; 
 scalar_t__ hdspm_set_pref_sync_ref (struct hdspm*,int) ; 
 int /*<<< orphan*/  snd_hdspm_use_is_exclusive (struct hdspm*) ; 
 struct hdspm* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_hdspm_put_pref_sync_ref(struct snd_kcontrol *kcontrol,
				       struct snd_ctl_elem_value *ucontrol)
{
	struct hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	int val, change = 0;

	if (!snd_hdspm_use_is_exclusive(hdspm))
		return -EBUSY;

	val = ucontrol->value.enumerated.item[0];

	if (val < 0)
		val = 0;
	else if (val >= hdspm->texts_autosync_items)
		val = hdspm->texts_autosync_items-1;

	spin_lock_irq(&hdspm->lock);
	if (val != hdspm_pref_sync_ref(hdspm))
		change = (0 == hdspm_set_pref_sync_ref(hdspm, val)) ? 1 : 0;

	spin_unlock_irq(&hdspm->lock);
	return change;
}
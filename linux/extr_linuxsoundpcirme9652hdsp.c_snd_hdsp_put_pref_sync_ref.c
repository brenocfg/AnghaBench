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
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hdsp {int io_type; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
#define  Digiface 131 
 int EBUSY ; 
 int EIO ; 
#define  H9632 130 
#define  H9652 129 
#define  Multiface 128 
 int hdsp_pref_sync_ref (struct hdsp*) ; 
 int /*<<< orphan*/  hdsp_set_pref_sync_ref (struct hdsp*,unsigned int) ; 
 int /*<<< orphan*/  snd_hdsp_use_is_exclusive (struct hdsp*) ; 
 struct hdsp* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_hdsp_put_pref_sync_ref(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	int change, max;
	unsigned int val;

	if (!snd_hdsp_use_is_exclusive(hdsp))
		return -EBUSY;

	switch (hdsp->io_type) {
	case Digiface:
	case H9652:
		max = 6;
		break;
	case Multiface:
		max = 4;
		break;
	case H9632:
		max = 3;
		break;
	default:
		return -EIO;
	}

	val = ucontrol->value.enumerated.item[0] % max;
	spin_lock_irq(&hdsp->lock);
	change = (int)val != hdsp_pref_sync_ref(hdsp);
	hdsp_set_pref_sync_ref(hdsp, val);
	spin_unlock_irq(&hdsp->lock);
	return change;
}
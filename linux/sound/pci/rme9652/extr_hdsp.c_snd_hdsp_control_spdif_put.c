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
typedef  scalar_t__ u32 ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  iec958; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;
struct hdsp {scalar_t__ creg_spdif; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ snd_hdsp_convert_from_aes (int /*<<< orphan*/ *) ; 
 struct hdsp* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_hdsp_control_spdif_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	int change;
	u32 val;

	val = snd_hdsp_convert_from_aes(&ucontrol->value.iec958);
	spin_lock_irq(&hdsp->lock);
	change = val != hdsp->creg_spdif;
	hdsp->creg_spdif = val;
	spin_unlock_irq(&hdsp->lock);
	return change;
}
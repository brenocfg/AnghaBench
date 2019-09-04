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
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct rme32 {unsigned int wcreg; int /*<<< orphan*/  lock; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ RME32_IO_CONTROL_REGISTER ; 
 unsigned int RME32_WCR_MUTE ; 
 unsigned int RME32_WCR_SEL ; 
 struct rme32* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int
snd_rme32_put_loopback_control(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct rme32 *rme32 = snd_kcontrol_chip(kcontrol);
	unsigned int val;
	int change;

	val = ucontrol->value.integer.value[0] ? 0 : RME32_WCR_SEL;
	spin_lock_irq(&rme32->lock);
	val = (rme32->wcreg & ~RME32_WCR_SEL) | val;
	change = val != rme32->wcreg;
	if (ucontrol->value.integer.value[0])
		val &= ~RME32_WCR_MUTE;
	else
		val |= RME32_WCR_MUTE;
	rme32->wcreg = val;
	writel(val, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	spin_unlock_irq(&rme32->lock);
	return change;
}
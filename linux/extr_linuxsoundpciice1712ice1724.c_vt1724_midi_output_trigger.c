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
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct snd_ice1712 {int midi_output; int /*<<< orphan*/  reg_lock; } ;
struct TYPE_2__ {struct snd_ice1712* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VT1724_IRQ_MPU_TX ; 
 int /*<<< orphan*/  enable_midi_irq (struct snd_ice1712*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vt1724_midi_write (struct snd_ice1712*) ; 

__attribute__((used)) static void vt1724_midi_output_trigger(struct snd_rawmidi_substream *s, int up)
{
	struct snd_ice1712 *ice = s->rmidi->private_data;
	unsigned long flags;

	spin_lock_irqsave(&ice->reg_lock, flags);
	if (up) {
		ice->midi_output = 1;
		vt1724_midi_write(ice);
	} else {
		ice->midi_output = 0;
		enable_midi_irq(ice, VT1724_IRQ_MPU_TX, 0);
	}
	spin_unlock_irqrestore(&ice->reg_lock, flags);
}
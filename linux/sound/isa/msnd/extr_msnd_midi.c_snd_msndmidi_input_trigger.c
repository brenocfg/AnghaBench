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
struct snd_msndmidi {int /*<<< orphan*/  input_lock; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {struct snd_msndmidi* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSNDMIDI_MODE_BIT_INPUT_TRIGGER ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_msndmidi_input_drop (struct snd_msndmidi*) ; 
 int /*<<< orphan*/  snd_msndmidi_input_read (struct snd_msndmidi*) ; 
 int /*<<< orphan*/  snd_printdd (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_msndmidi_input_trigger(struct snd_rawmidi_substream *substream,
					int up)
{
	unsigned long flags;
	struct snd_msndmidi *mpu;

	snd_printdd("snd_msndmidi_input_trigger(, %i)\n", up);

	mpu = substream->rmidi->private_data;
	spin_lock_irqsave(&mpu->input_lock, flags);
	if (up) {
		if (!test_and_set_bit(MSNDMIDI_MODE_BIT_INPUT_TRIGGER,
				      &mpu->mode))
			snd_msndmidi_input_drop(mpu);
	} else {
		clear_bit(MSNDMIDI_MODE_BIT_INPUT_TRIGGER, &mpu->mode);
	}
	spin_unlock_irqrestore(&mpu->input_lock, flags);
	if (up)
		snd_msndmidi_input_read(mpu);
}
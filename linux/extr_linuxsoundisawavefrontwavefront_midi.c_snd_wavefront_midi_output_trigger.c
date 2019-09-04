#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_rawmidi_substream {TYPE_2__* rmidi; } ;
typedef  size_t snd_wavefront_mpu_id ;
struct TYPE_7__ {int* mode; int /*<<< orphan*/  virtual; int /*<<< orphan*/  istimer; int /*<<< orphan*/  timer; } ;
typedef  TYPE_3__ snd_wavefront_midi_t ;
typedef  int /*<<< orphan*/  snd_wavefront_card_t ;
struct TYPE_6__ {TYPE_1__* card; int /*<<< orphan*/ * private_data; } ;
struct TYPE_5__ {scalar_t__ private_data; } ;

/* Variables and functions */
 int MPU401_MODE_OUTPUT_TRIGGER ; 
 TYPE_3__* get_wavefront_midi (struct snd_rawmidi_substream*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  snd_wavefront_midi_output_timer ; 
 int /*<<< orphan*/  snd_wavefront_midi_output_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_wavefront_midi_output_trigger(struct snd_rawmidi_substream *substream, int up)
{
	unsigned long flags;
	snd_wavefront_midi_t *midi;
	snd_wavefront_mpu_id mpu;

	if (substream == NULL || substream->rmidi == NULL) 
	        return;

	if (substream->rmidi->private_data == NULL)
	        return;

	mpu = *((snd_wavefront_mpu_id *) substream->rmidi->private_data);

	if ((midi = get_wavefront_midi (substream)) == NULL) {
		return;
	}

	spin_lock_irqsave (&midi->virtual, flags);
	if (up) {
		if ((midi->mode[mpu] & MPU401_MODE_OUTPUT_TRIGGER) == 0) {
			if (!midi->istimer) {
				timer_setup(&midi->timer,
					    snd_wavefront_midi_output_timer,
					    0);
				mod_timer(&midi->timer, 1 + jiffies);
			}
			midi->istimer++;
			midi->mode[mpu] |= MPU401_MODE_OUTPUT_TRIGGER;
		}
	} else {
		midi->mode[mpu] &= ~MPU401_MODE_OUTPUT_TRIGGER;
	}
	spin_unlock_irqrestore (&midi->virtual, flags);

	if (up)
		snd_wavefront_midi_output_write((snd_wavefront_card_t *)substream->rmidi->card->private_data);
}
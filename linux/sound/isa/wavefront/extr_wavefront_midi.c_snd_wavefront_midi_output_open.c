#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
typedef  size_t snd_wavefront_mpu_id ;
struct TYPE_5__ {int /*<<< orphan*/  open; struct snd_rawmidi_substream** substream_output; int /*<<< orphan*/ * mode; } ;
typedef  TYPE_2__ snd_wavefront_midi_t ;
struct TYPE_4__ {scalar_t__ private_data; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  MPU401_MODE_OUTPUT ; 
 TYPE_2__* get_wavefront_midi (struct snd_rawmidi_substream*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_wavefront_midi_output_open(struct snd_rawmidi_substream *substream)
{
	unsigned long flags;
	snd_wavefront_midi_t *midi;
	snd_wavefront_mpu_id mpu;

	if (snd_BUG_ON(!substream || !substream->rmidi))
		return -ENXIO;
	if (snd_BUG_ON(!substream->rmidi->private_data))
		return -ENXIO;

	mpu = *((snd_wavefront_mpu_id *) substream->rmidi->private_data);

	if ((midi = get_wavefront_midi (substream)) == NULL)
	        return -EIO;

	spin_lock_irqsave (&midi->open, flags);
	midi->mode[mpu] |= MPU401_MODE_OUTPUT;
	midi->substream_output[mpu] = substream;
	spin_unlock_irqrestore (&midi->open, flags);

	return 0;
}
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
struct snd_msndmidi {int /*<<< orphan*/  mode; int /*<<< orphan*/  dev; struct snd_rawmidi_substream* substream_input; } ;
struct TYPE_2__ {struct snd_msndmidi* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDEX_MIDI_IN_START ; 
 int /*<<< orphan*/  MSNDMIDI_MODE_BIT_INPUT ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_msnd_enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_msnd_send_dsp_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_printdd (char*) ; 

__attribute__((used)) static int snd_msndmidi_input_open(struct snd_rawmidi_substream *substream)
{
	struct snd_msndmidi *mpu;

	snd_printdd("snd_msndmidi_input_open()\n");

	mpu = substream->rmidi->private_data;

	mpu->substream_input = substream;

	snd_msnd_enable_irq(mpu->dev);

	snd_msnd_send_dsp_cmd(mpu->dev, HDEX_MIDI_IN_START);
	set_bit(MSNDMIDI_MODE_BIT_INPUT, &mpu->mode);
	return 0;
}
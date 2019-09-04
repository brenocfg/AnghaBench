#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_sb {scalar_t__ hardware; struct snd_rawmidi* rmidi; int /*<<< orphan*/  midi_timer; int /*<<< orphan*/  card; } ;
struct snd_rawmidi {int info_flags; struct snd_sb* private_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ SB_HW_20 ; 
 int SNDRV_RAWMIDI_INFO_DUPLEX ; 
 int SNDRV_RAWMIDI_INFO_INPUT ; 
 int SNDRV_RAWMIDI_INFO_OUTPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_INPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_OUTPUT ; 
 int snd_rawmidi_new (int /*<<< orphan*/ ,char*,int,int,int,struct snd_rawmidi**) ; 
 int /*<<< orphan*/  snd_rawmidi_set_ops (struct snd_rawmidi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_sb8dsp_midi_input ; 
 int /*<<< orphan*/  snd_sb8dsp_midi_output ; 
 int /*<<< orphan*/  snd_sb8dsp_midi_output_timer ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_sb8dsp_midi(struct snd_sb *chip, int device)
{
	struct snd_rawmidi *rmidi;
	int err;

	if ((err = snd_rawmidi_new(chip->card, "SB8 MIDI", device, 1, 1, &rmidi)) < 0)
		return err;
	strcpy(rmidi->name, "SB8 MIDI");
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &snd_sb8dsp_midi_output);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &snd_sb8dsp_midi_input);
	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT | SNDRV_RAWMIDI_INFO_INPUT;
	if (chip->hardware >= SB_HW_20)
		rmidi->info_flags |= SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->private_data = chip;
	timer_setup(&chip->midi_timer, snd_sb8dsp_midi_output_timer, 0);
	chip->rmidi = rmidi;
	return 0;
}
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
struct snd_rawmidi {int info_flags; struct cs4281* private_data; int /*<<< orphan*/  name; } ;
struct cs4281 {struct snd_rawmidi* rmidi; int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int SNDRV_RAWMIDI_INFO_DUPLEX ; 
 int SNDRV_RAWMIDI_INFO_INPUT ; 
 int SNDRV_RAWMIDI_INFO_OUTPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_INPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_OUTPUT ; 
 int /*<<< orphan*/  snd_cs4281_midi_input ; 
 int /*<<< orphan*/  snd_cs4281_midi_output ; 
 int snd_rawmidi_new (int /*<<< orphan*/ ,char*,int,int,int,struct snd_rawmidi**) ; 
 int /*<<< orphan*/  snd_rawmidi_set_ops (struct snd_rawmidi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_cs4281_midi(struct cs4281 *chip, int device)
{
	struct snd_rawmidi *rmidi;
	int err;

	if ((err = snd_rawmidi_new(chip->card, "CS4281", device, 1, 1, &rmidi)) < 0)
		return err;
	strcpy(rmidi->name, "CS4281");
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &snd_cs4281_midi_output);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &snd_cs4281_midi_input);
	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT | SNDRV_RAWMIDI_INFO_INPUT | SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->private_data = chip;
	chip->rmidi = rmidi;
	return 0;
}
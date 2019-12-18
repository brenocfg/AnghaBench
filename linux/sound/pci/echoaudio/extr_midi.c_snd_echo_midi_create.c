#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_card {int /*<<< orphan*/  shortname; } ;
struct echoaudio {TYPE_1__* rmidi; } ;
struct TYPE_3__ {int info_flags; struct echoaudio* private_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int SNDRV_RAWMIDI_INFO_DUPLEX ; 
 int SNDRV_RAWMIDI_INFO_INPUT ; 
 int SNDRV_RAWMIDI_INFO_OUTPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_INPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_OUTPUT ; 
 int /*<<< orphan*/  snd_echo_midi_input ; 
 int /*<<< orphan*/  snd_echo_midi_output ; 
 int snd_rawmidi_new (struct snd_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,TYPE_1__**) ; 
 int /*<<< orphan*/  snd_rawmidi_set_ops (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_echo_midi_create(struct snd_card *card,
				struct echoaudio *chip)
{
	int err;

	if ((err = snd_rawmidi_new(card, card->shortname, 0, 1, 1,
				   &chip->rmidi)) < 0)
		return err;

	strcpy(chip->rmidi->name, card->shortname);
	chip->rmidi->private_data = chip;

	snd_rawmidi_set_ops(chip->rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
			    &snd_echo_midi_input);
	snd_rawmidi_set_ops(chip->rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
			    &snd_echo_midi_output);

	chip->rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT |
		SNDRV_RAWMIDI_INFO_INPUT | SNDRV_RAWMIDI_INFO_DUPLEX;
	return 0;
}
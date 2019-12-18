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
struct usb_line6 {TYPE_1__* properties; int /*<<< orphan*/  card; } ;
struct snd_rawmidi {int info_flags; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int SNDRV_RAWMIDI_INFO_DUPLEX ; 
 int SNDRV_RAWMIDI_INFO_INPUT ; 
 int SNDRV_RAWMIDI_INFO_OUTPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_INPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_OUTPUT ; 
 int /*<<< orphan*/  line6_midi_input_ops ; 
 int /*<<< orphan*/  line6_midi_output_ops ; 
 int snd_rawmidi_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,struct snd_rawmidi**) ; 
 int /*<<< orphan*/  snd_rawmidi_set_ops (struct snd_rawmidi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_line6_new_midi(struct usb_line6 *line6,
			      struct snd_rawmidi **rmidi_ret)
{
	struct snd_rawmidi *rmidi;
	int err;

	err = snd_rawmidi_new(line6->card, "Line 6 MIDI", 0, 1, 1, rmidi_ret);
	if (err < 0)
		return err;

	rmidi = *rmidi_ret;
	strcpy(rmidi->id, line6->properties->id);
	strcpy(rmidi->name, line6->properties->name);

	rmidi->info_flags =
	    SNDRV_RAWMIDI_INFO_OUTPUT |
	    SNDRV_RAWMIDI_INFO_INPUT | SNDRV_RAWMIDI_INFO_DUPLEX;

	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
			    &line6_midi_output_ops);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
			    &line6_midi_input_ops);
	return 0;
}
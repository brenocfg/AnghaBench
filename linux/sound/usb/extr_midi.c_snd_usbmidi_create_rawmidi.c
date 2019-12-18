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
struct snd_usb_midi {struct snd_rawmidi* rmidi; TYPE_1__* card; int /*<<< orphan*/  next_midi_device; } ;
struct snd_rawmidi {int info_flags; int /*<<< orphan*/  private_free; struct snd_usb_midi* private_data; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  shortname; } ;

/* Variables and functions */
 int SNDRV_RAWMIDI_INFO_DUPLEX ; 
 int SNDRV_RAWMIDI_INFO_INPUT ; 
 int SNDRV_RAWMIDI_INFO_OUTPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_INPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_OUTPUT ; 
 int snd_rawmidi_new (TYPE_1__*,char*,int /*<<< orphan*/ ,int,int,struct snd_rawmidi**) ; 
 int /*<<< orphan*/  snd_rawmidi_set_ops (struct snd_rawmidi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_usbmidi_input_ops ; 
 int /*<<< orphan*/  snd_usbmidi_ops ; 
 int /*<<< orphan*/  snd_usbmidi_output_ops ; 
 int /*<<< orphan*/  snd_usbmidi_rawmidi_free ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_usbmidi_create_rawmidi(struct snd_usb_midi *umidi,
				      int out_ports, int in_ports)
{
	struct snd_rawmidi *rmidi;
	int err;

	err = snd_rawmidi_new(umidi->card, "USB MIDI",
			      umidi->next_midi_device++,
			      out_ports, in_ports, &rmidi);
	if (err < 0)
		return err;
	strcpy(rmidi->name, umidi->card->shortname);
	rmidi->info_flags = SNDRV_RAWMIDI_INFO_OUTPUT |
			    SNDRV_RAWMIDI_INFO_INPUT |
			    SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->ops = &snd_usbmidi_ops;
	rmidi->private_data = umidi;
	rmidi->private_free = snd_usbmidi_rawmidi_free;
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
			    &snd_usbmidi_output_ops);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
			    &snd_usbmidi_input_ops);

	umidi->rmidi = rmidi;
	return 0;
}
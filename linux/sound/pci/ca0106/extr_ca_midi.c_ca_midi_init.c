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
struct snd_rawmidi {int info_flags; int /*<<< orphan*/  private_free; struct snd_ca_midi* private_data; int /*<<< orphan*/  name; } ;
struct snd_ca_midi {struct snd_rawmidi* rmidi; int /*<<< orphan*/  output_lock; int /*<<< orphan*/  input_lock; int /*<<< orphan*/  open_lock; int /*<<< orphan*/  interrupt; void* dev_id; int /*<<< orphan*/  (* get_dev_id_card ) (void*) ;} ;

/* Variables and functions */
 int SNDRV_RAWMIDI_INFO_DUPLEX ; 
 int SNDRV_RAWMIDI_INFO_INPUT ; 
 int SNDRV_RAWMIDI_INFO_OUTPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_INPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_OUTPUT ; 
 int /*<<< orphan*/  ca_midi_input ; 
 int /*<<< orphan*/  ca_midi_interrupt ; 
 int /*<<< orphan*/  ca_midi_output ; 
 int /*<<< orphan*/  ca_rmidi_free ; 
 int snd_rawmidi_new (int /*<<< orphan*/ ,char*,int,int,int,struct snd_rawmidi**) ; 
 int /*<<< orphan*/  snd_rawmidi_set_ops (struct snd_rawmidi*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

int ca_midi_init(void *dev_id, struct snd_ca_midi *midi, int device, char *name)
{
	struct snd_rawmidi *rmidi;
	int err;

	if ((err = snd_rawmidi_new(midi->get_dev_id_card(midi->dev_id), name, device, 1, 1, &rmidi)) < 0)
		return err;

	midi->dev_id = dev_id;
	midi->interrupt = ca_midi_interrupt;

	spin_lock_init(&midi->open_lock);
	spin_lock_init(&midi->input_lock);
	spin_lock_init(&midi->output_lock);

	strcpy(rmidi->name, name);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &ca_midi_output);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &ca_midi_input);
	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT |
	                     SNDRV_RAWMIDI_INFO_INPUT |
	                     SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->private_data = midi;
	rmidi->private_free = ca_rmidi_free;
	
	midi->rmidi = rmidi;
	return 0;
}
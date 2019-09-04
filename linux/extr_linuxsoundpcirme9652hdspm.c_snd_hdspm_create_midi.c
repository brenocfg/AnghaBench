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
struct snd_card {char* shortname; char* id; } ;
struct hdspm {scalar_t__ io_type; TYPE_1__* midi; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {char* name; int info_flags; TYPE_1__* private_data; } ;
struct TYPE_4__ {int id; int dataOut; int statusOut; TYPE_2__* rmidi; void* irq; void* ie; void* statusIn; void* dataIn; int /*<<< orphan*/  lock; struct hdspm* hdspm; } ;

/* Variables and functions */
 void* HDSPM_Midi0InterruptEnable ; 
 void* HDSPM_Midi1InterruptEnable ; 
 void* HDSPM_Midi2InterruptEnable ; 
 void* HDSPM_Midi3InterruptEnable ; 
 void* HDSPM_midi0IRQPending ; 
 void* HDSPM_midi1IRQPending ; 
 void* HDSPM_midi2IRQPending ; 
 void* HDSPM_midi2IRQPendingAES ; 
 void* HDSPM_midi3IRQPending ; 
 void* HDSPM_midiDataIn0 ; 
 void* HDSPM_midiDataIn1 ; 
 void* HDSPM_midiDataIn2 ; 
 void* HDSPM_midiDataIn3 ; 
 int HDSPM_midiDataOut0 ; 
 int HDSPM_midiDataOut1 ; 
 void* HDSPM_midiDataOut2 ; 
 void* HDSPM_midiStatusIn0 ; 
 void* HDSPM_midiStatusIn1 ; 
 void* HDSPM_midiStatusIn2 ; 
 void* HDSPM_midiStatusIn3 ; 
 int HDSPM_midiStatusOut0 ; 
 int HDSPM_midiStatusOut1 ; 
 void* HDSPM_midiStatusOut2 ; 
 scalar_t__ MADI ; 
 scalar_t__ MADIface ; 
 int SNDRV_RAWMIDI_INFO_DUPLEX ; 
 int SNDRV_RAWMIDI_INFO_INPUT ; 
 int SNDRV_RAWMIDI_INFO_OUTPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_INPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_OUTPUT ; 
 int /*<<< orphan*/  snd_hdspm_midi_input ; 
 int /*<<< orphan*/  snd_hdspm_midi_output ; 
 int snd_rawmidi_new (struct snd_card*,char*,int,int,int,TYPE_2__**) ; 
 int /*<<< orphan*/  snd_rawmidi_set_ops (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_hdspm_create_midi(struct snd_card *card,
				 struct hdspm *hdspm, int id)
{
	int err;
	char buf[64];

	hdspm->midi[id].id = id;
	hdspm->midi[id].hdspm = hdspm;
	spin_lock_init (&hdspm->midi[id].lock);

	if (0 == id) {
		if (MADIface == hdspm->io_type) {
			/* MIDI-over-MADI on HDSPe MADIface */
			hdspm->midi[0].dataIn = HDSPM_midiDataIn2;
			hdspm->midi[0].statusIn = HDSPM_midiStatusIn2;
			hdspm->midi[0].dataOut = HDSPM_midiDataOut2;
			hdspm->midi[0].statusOut = HDSPM_midiStatusOut2;
			hdspm->midi[0].ie = HDSPM_Midi2InterruptEnable;
			hdspm->midi[0].irq = HDSPM_midi2IRQPending;
		} else {
			hdspm->midi[0].dataIn = HDSPM_midiDataIn0;
			hdspm->midi[0].statusIn = HDSPM_midiStatusIn0;
			hdspm->midi[0].dataOut = HDSPM_midiDataOut0;
			hdspm->midi[0].statusOut = HDSPM_midiStatusOut0;
			hdspm->midi[0].ie = HDSPM_Midi0InterruptEnable;
			hdspm->midi[0].irq = HDSPM_midi0IRQPending;
		}
	} else if (1 == id) {
		hdspm->midi[1].dataIn = HDSPM_midiDataIn1;
		hdspm->midi[1].statusIn = HDSPM_midiStatusIn1;
		hdspm->midi[1].dataOut = HDSPM_midiDataOut1;
		hdspm->midi[1].statusOut = HDSPM_midiStatusOut1;
		hdspm->midi[1].ie = HDSPM_Midi1InterruptEnable;
		hdspm->midi[1].irq = HDSPM_midi1IRQPending;
	} else if ((2 == id) && (MADI == hdspm->io_type)) {
		/* MIDI-over-MADI on HDSPe MADI */
		hdspm->midi[2].dataIn = HDSPM_midiDataIn2;
		hdspm->midi[2].statusIn = HDSPM_midiStatusIn2;
		hdspm->midi[2].dataOut = HDSPM_midiDataOut2;
		hdspm->midi[2].statusOut = HDSPM_midiStatusOut2;
		hdspm->midi[2].ie = HDSPM_Midi2InterruptEnable;
		hdspm->midi[2].irq = HDSPM_midi2IRQPending;
	} else if (2 == id) {
		/* TCO MTC, read only */
		hdspm->midi[2].dataIn = HDSPM_midiDataIn2;
		hdspm->midi[2].statusIn = HDSPM_midiStatusIn2;
		hdspm->midi[2].dataOut = -1;
		hdspm->midi[2].statusOut = -1;
		hdspm->midi[2].ie = HDSPM_Midi2InterruptEnable;
		hdspm->midi[2].irq = HDSPM_midi2IRQPendingAES;
	} else if (3 == id) {
		/* TCO MTC on HDSPe MADI */
		hdspm->midi[3].dataIn = HDSPM_midiDataIn3;
		hdspm->midi[3].statusIn = HDSPM_midiStatusIn3;
		hdspm->midi[3].dataOut = -1;
		hdspm->midi[3].statusOut = -1;
		hdspm->midi[3].ie = HDSPM_Midi3InterruptEnable;
		hdspm->midi[3].irq = HDSPM_midi3IRQPending;
	}

	if ((id < 2) || ((2 == id) && ((MADI == hdspm->io_type) ||
					(MADIface == hdspm->io_type)))) {
		if ((id == 0) && (MADIface == hdspm->io_type)) {
			snprintf(buf, sizeof(buf), "%s MIDIoverMADI",
				 card->shortname);
		} else if ((id == 2) && (MADI == hdspm->io_type)) {
			snprintf(buf, sizeof(buf), "%s MIDIoverMADI",
				 card->shortname);
		} else {
			snprintf(buf, sizeof(buf), "%s MIDI %d",
				 card->shortname, id+1);
		}
		err = snd_rawmidi_new(card, buf, id, 1, 1,
				&hdspm->midi[id].rmidi);
		if (err < 0)
			return err;

		snprintf(hdspm->midi[id].rmidi->name,
			 sizeof(hdspm->midi[id].rmidi->name),
			 "%s MIDI %d", card->id, id+1);
		hdspm->midi[id].rmidi->private_data = &hdspm->midi[id];

		snd_rawmidi_set_ops(hdspm->midi[id].rmidi,
				SNDRV_RAWMIDI_STREAM_OUTPUT,
				&snd_hdspm_midi_output);
		snd_rawmidi_set_ops(hdspm->midi[id].rmidi,
				SNDRV_RAWMIDI_STREAM_INPUT,
				&snd_hdspm_midi_input);

		hdspm->midi[id].rmidi->info_flags |=
			SNDRV_RAWMIDI_INFO_OUTPUT |
			SNDRV_RAWMIDI_INFO_INPUT |
			SNDRV_RAWMIDI_INFO_DUPLEX;
	} else {
		/* TCO MTC, read only */
		snprintf(buf, sizeof(buf), "%s MTC %d",
			 card->shortname, id+1);
		err = snd_rawmidi_new(card, buf, id, 1, 1,
				&hdspm->midi[id].rmidi);
		if (err < 0)
			return err;

		snprintf(hdspm->midi[id].rmidi->name,
			 sizeof(hdspm->midi[id].rmidi->name),
			 "%s MTC %d", card->id, id+1);
		hdspm->midi[id].rmidi->private_data = &hdspm->midi[id];

		snd_rawmidi_set_ops(hdspm->midi[id].rmidi,
				SNDRV_RAWMIDI_STREAM_INPUT,
				&snd_hdspm_midi_input);

		hdspm->midi[id].rmidi->info_flags |= SNDRV_RAWMIDI_INFO_INPUT;
	}

	return 0;
}
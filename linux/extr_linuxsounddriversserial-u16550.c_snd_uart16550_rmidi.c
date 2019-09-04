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
struct snd_uart16550 {int /*<<< orphan*/  card; } ;
struct snd_rawmidi {int info_flags; struct snd_uart16550* private_data; int /*<<< orphan*/ * streams; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int SNDRV_RAWMIDI_INFO_DUPLEX ; 
 int SNDRV_RAWMIDI_INFO_INPUT ; 
 int SNDRV_RAWMIDI_INFO_OUTPUT ; 
 size_t SNDRV_RAWMIDI_STREAM_INPUT ; 
 size_t SNDRV_RAWMIDI_STREAM_OUTPUT ; 
 int snd_rawmidi_new (int /*<<< orphan*/ ,char*,int,int,int,struct snd_rawmidi**) ; 
 int /*<<< orphan*/  snd_rawmidi_set_ops (struct snd_rawmidi*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_uart16550_input ; 
 int /*<<< orphan*/  snd_uart16550_output ; 
 int /*<<< orphan*/  snd_uart16550_substreams (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int snd_uart16550_rmidi(struct snd_uart16550 *uart, int device,
			       int outs, int ins,
			       struct snd_rawmidi **rmidi)
{
	struct snd_rawmidi *rrawmidi;
	int err;

	err = snd_rawmidi_new(uart->card, "UART Serial MIDI", device,
			      outs, ins, &rrawmidi);
	if (err < 0)
		return err;
	snd_rawmidi_set_ops(rrawmidi, SNDRV_RAWMIDI_STREAM_INPUT,
			    &snd_uart16550_input);
	snd_rawmidi_set_ops(rrawmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
			    &snd_uart16550_output);
	strcpy(rrawmidi->name, "Serial MIDI");
	snd_uart16550_substreams(&rrawmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT]);
	snd_uart16550_substreams(&rrawmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT]);
	rrawmidi->info_flags = SNDRV_RAWMIDI_INFO_OUTPUT |
			       SNDRV_RAWMIDI_INFO_INPUT |
			       SNDRV_RAWMIDI_INFO_DUPLEX;
	rrawmidi->private_data = uart;
	if (rmidi)
		*rmidi = rrawmidi;
	return 0;
}
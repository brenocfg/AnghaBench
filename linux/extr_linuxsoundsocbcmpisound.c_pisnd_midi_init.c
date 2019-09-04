#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_card {int dummy; } ;
struct TYPE_4__ {int info_flags; void* private_data; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int SNDRV_RAWMIDI_INFO_DUPLEX ; 
 int SNDRV_RAWMIDI_INFO_INPUT ; 
 int SNDRV_RAWMIDI_INFO_OUTPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_INPUT ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_OUTPUT ; 
 int /*<<< orphan*/ * g_midi_output_substream ; 
 TYPE_1__* g_rmidi ; 
 int /*<<< orphan*/  pisnd_global_ops ; 
 int /*<<< orphan*/  pisnd_input_ops ; 
 int /*<<< orphan*/  pisnd_output_ops ; 
 int /*<<< orphan*/  pisnd_spi_get_serial () ; 
 int /*<<< orphan*/  printe (char*,int) ; 
 int snd_rawmidi_new (struct snd_card*,char*,int /*<<< orphan*/ ,int,int,TYPE_1__**) ; 
 int /*<<< orphan*/  snd_rawmidi_set_ops (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int pisnd_midi_init(struct snd_card *card)
{
	int err;

	g_midi_output_substream = NULL;

	err = snd_rawmidi_new(card, "pisound MIDI", 0, 1, 1, &g_rmidi);

	if (err < 0) {
		printe("snd_rawmidi_new failed: %d\n", err);
		return err;
	}

	strcpy(g_rmidi->name, "pisound MIDI ");
	strcat(g_rmidi->name, pisnd_spi_get_serial());

	g_rmidi->info_flags =
		SNDRV_RAWMIDI_INFO_OUTPUT |
		SNDRV_RAWMIDI_INFO_INPUT |
		SNDRV_RAWMIDI_INFO_DUPLEX;

	g_rmidi->ops = &pisnd_global_ops;

	g_rmidi->private_data = (void *)0;

	snd_rawmidi_set_ops(
		g_rmidi,
		SNDRV_RAWMIDI_STREAM_OUTPUT,
		&pisnd_output_ops
		);

	snd_rawmidi_set_ops(
		g_rmidi,
		SNDRV_RAWMIDI_STREAM_INPUT,
		&pisnd_input_ops
		);

	return 0;
}
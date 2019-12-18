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
struct snd_info_entry {struct snd_dice* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct snd_dice {int** tx_pcm_chs; int* tx_midi_ports; int** rx_pcm_chs; int* rx_midi_ports; } ;

/* Variables and functions */
 int MAX_STREAMS ; 
 int SND_DICE_RATE_MODE_COUNT ; 
#define  SND_DICE_RATE_MODE_HIGH 130 
#define  SND_DICE_RATE_MODE_LOW 129 
#define  SND_DICE_RATE_MODE_MIDDLE 128 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void dice_proc_read_formation(struct snd_info_entry *entry,
				     struct snd_info_buffer *buffer)
{
	static const char *const rate_labels[] = {
		[SND_DICE_RATE_MODE_LOW]	= "low",
		[SND_DICE_RATE_MODE_MIDDLE]	= "middle",
		[SND_DICE_RATE_MODE_HIGH]	= "high",
	};
	struct snd_dice *dice = entry->private_data;
	int i, j;

	snd_iprintf(buffer, "Output stream from unit:\n");
	for (i = 0; i < SND_DICE_RATE_MODE_COUNT; ++i)
		snd_iprintf(buffer, "\t%s", rate_labels[i]);
	snd_iprintf(buffer, "\tMIDI\n");
	for (i = 0; i < MAX_STREAMS; ++i) {
		snd_iprintf(buffer, "Tx %u:", i);
		for (j = 0; j < SND_DICE_RATE_MODE_COUNT; ++j)
			snd_iprintf(buffer, "\t%u", dice->tx_pcm_chs[i][j]);
		snd_iprintf(buffer, "\t%u\n", dice->tx_midi_ports[i]);
	}

	snd_iprintf(buffer, "Input stream to unit:\n");
	for (i = 0; i < SND_DICE_RATE_MODE_COUNT; ++i)
		snd_iprintf(buffer, "\t%s", rate_labels[i]);
	snd_iprintf(buffer, "\n");
	for (i = 0; i < MAX_STREAMS; ++i) {
		snd_iprintf(buffer, "Rx %u:", i);
		for (j = 0; j < SND_DICE_RATE_MODE_COUNT; ++j)
			snd_iprintf(buffer, "\t%u", dice->rx_pcm_chs[i][j]);
		snd_iprintf(buffer, "\t%u\n", dice->rx_midi_ports[i]);
	}
}
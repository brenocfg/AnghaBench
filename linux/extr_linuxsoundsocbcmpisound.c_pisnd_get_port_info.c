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
struct snd_seq_port_info {int type; scalar_t__ midi_voices; } ;
struct snd_rawmidi {int dummy; } ;

/* Variables and functions */
 int SNDRV_SEQ_PORT_TYPE_HARDWARE ; 
 int SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC ; 
 int SNDRV_SEQ_PORT_TYPE_PORT ; 

__attribute__((used)) static void pisnd_get_port_info(
	struct snd_rawmidi *rmidi,
	int number,
	struct snd_seq_port_info *seq_port_info
	)
{
	seq_port_info->type =
		SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC |
		SNDRV_SEQ_PORT_TYPE_HARDWARE |
		SNDRV_SEQ_PORT_TYPE_PORT;
	seq_port_info->midi_voices = 0;
}
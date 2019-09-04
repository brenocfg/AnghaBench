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
struct snd_usb_midi {int dummy; } ;
struct snd_seq_port_info {int /*<<< orphan*/  midi_voices; int /*<<< orphan*/  type; } ;
struct snd_rawmidi {struct snd_usb_midi* private_data; } ;
struct port_info {int /*<<< orphan*/  voices; int /*<<< orphan*/  seq_flags; } ;

/* Variables and functions */
 struct port_info* find_port_info (struct snd_usb_midi*,int) ; 

__attribute__((used)) static void snd_usbmidi_get_port_info(struct snd_rawmidi *rmidi, int number,
				      struct snd_seq_port_info *seq_port_info)
{
	struct snd_usb_midi *umidi = rmidi->private_data;
	struct port_info *port_info;

	/* TODO: read port flags from descriptors */
	port_info = find_port_info(umidi, number);
	if (port_info) {
		seq_port_info->type = port_info->seq_flags;
		seq_port_info->midi_voices = port_info->voices;
	}
}
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
typedef  int u8 ;
struct snd_rawmidi_substream {int dummy; } ;
struct mtpav_port {int hwport; int running_status; } ;
struct mtpav {int outmidihwport; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_mtpav_send_byte (struct mtpav*,int) ; 
 int snd_rawmidi_transmit (struct snd_rawmidi_substream*,int*,int) ; 

__attribute__((used)) static void snd_mtpav_output_port_write(struct mtpav *mtp_card,
					struct mtpav_port *portp,
					struct snd_rawmidi_substream *substream)
{
	u8 outbyte;

	// Get the outbyte first, so we can emulate running status if
	// necessary
	if (snd_rawmidi_transmit(substream, &outbyte, 1) != 1)
		return;

	// send port change command if necessary

	if (portp->hwport != mtp_card->outmidihwport) {
		mtp_card->outmidihwport = portp->hwport;

		snd_mtpav_send_byte(mtp_card, 0xf5);
		snd_mtpav_send_byte(mtp_card, portp->hwport);
		/*
		snd_printk(KERN_DEBUG "new outport: 0x%x\n",
			   (unsigned int) portp->hwport);
		*/
		if (!(outbyte & 0x80) && portp->running_status)
			snd_mtpav_send_byte(mtp_card, portp->running_status);
	}

	// send data

	do {
		if (outbyte & 0x80)
			portp->running_status = outbyte;
		
		snd_mtpav_send_byte(mtp_card, outbyte);
	} while (snd_rawmidi_transmit(substream, &outbyte, 1) == 1);
}
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
struct TYPE_2__ {int uart_cmd; } ;
struct snd_gus_card {int /*<<< orphan*/  uart_cmd_lock; TYPE_1__ gf1; int /*<<< orphan*/  midi_substream_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_gf1_interrupt_midi_in (struct snd_gus_card*) ; 
 int /*<<< orphan*/  snd_gf1_uart_cmd (struct snd_gus_card*,int) ; 
 int /*<<< orphan*/  snd_gf1_uart_put (struct snd_gus_card*,char) ; 
 int snd_gf1_uart_stat (struct snd_gus_card*) ; 
 int snd_rawmidi_transmit (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_gf1_interrupt_midi_out(struct snd_gus_card * gus)
{
	char byte;
	unsigned long flags;

	/* try unlock output */
	if (snd_gf1_uart_stat(gus) & 0x01)
		snd_gf1_interrupt_midi_in(gus);

	spin_lock_irqsave(&gus->uart_cmd_lock, flags);
	if (snd_gf1_uart_stat(gus) & 0x02) {	/* Tx FIFO free? */
		if (snd_rawmidi_transmit(gus->midi_substream_output, &byte, 1) != 1) {	/* no other bytes or error */
			snd_gf1_uart_cmd(gus, gus->gf1.uart_cmd & ~0x20); /* disable Tx interrupt */
		} else {
			snd_gf1_uart_put(gus, byte);
		}
	}
	spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
}
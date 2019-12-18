#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct TYPE_4__ {int uart_cmd; } ;
struct snd_gus_card {int /*<<< orphan*/  uart_cmd_lock; TYPE_2__ gf1; } ;
struct TYPE_3__ {struct snd_gus_card* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_gf1_uart_cmd (struct snd_gus_card*,int) ; 
 int /*<<< orphan*/  snd_gf1_uart_put (struct snd_gus_card*,char) ; 
 int snd_gf1_uart_stat (struct snd_gus_card*) ; 
 int snd_rawmidi_transmit (struct snd_rawmidi_substream*,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_gf1_uart_output_trigger(struct snd_rawmidi_substream *substream, int up)
{
	unsigned long flags;
	struct snd_gus_card *gus;
	char byte;
	int timeout;

	gus = substream->rmidi->private_data;

	spin_lock_irqsave(&gus->uart_cmd_lock, flags);
	if (up) {
		if ((gus->gf1.uart_cmd & 0x20) == 0) {
			spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
			/* wait for empty Rx - Tx is probably unlocked */
			timeout = 10000;
			while (timeout-- > 0 && snd_gf1_uart_stat(gus) & 0x01);
			/* Tx FIFO free? */
			spin_lock_irqsave(&gus->uart_cmd_lock, flags);
			if (gus->gf1.uart_cmd & 0x20) {
				spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
				return;
			}
			if (snd_gf1_uart_stat(gus) & 0x02) {
				if (snd_rawmidi_transmit(substream, &byte, 1) != 1) {
					spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
					return;
				}
				snd_gf1_uart_put(gus, byte);
			}
			snd_gf1_uart_cmd(gus, gus->gf1.uart_cmd | 0x20);	/* enable Tx interrupt */
		}
	} else {
		if (gus->gf1.uart_cmd & 0x20)
			snd_gf1_uart_cmd(gus, gus->gf1.uart_cmd & ~0x20);
	}
	spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
}
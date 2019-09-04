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
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct ensoniq {unsigned char uartc; int /*<<< orphan*/  reg_lock; } ;
struct TYPE_2__ {struct ensoniq* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ES_REG (struct ensoniq*,int /*<<< orphan*/ ) ; 
 int ES_TXINTENI (unsigned char) ; 
 unsigned char ES_TXINTENM ; 
 unsigned char ES_TXINTENO (int) ; 
 int ES_TXRDY ; 
 int /*<<< orphan*/  UART_CONTROL ; 
 int /*<<< orphan*/  UART_DATA ; 
 int /*<<< orphan*/  UART_STATUS ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int snd_rawmidi_transmit (struct snd_rawmidi_substream*,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_ensoniq_midi_output_trigger(struct snd_rawmidi_substream *substream, int up)
{
	unsigned long flags;
	struct ensoniq *ensoniq = substream->rmidi->private_data;
	unsigned char byte;

	spin_lock_irqsave(&ensoniq->reg_lock, flags);
	if (up) {
		if (ES_TXINTENI(ensoniq->uartc) == 0) {
			ensoniq->uartc |= ES_TXINTENO(1);
			/* fill UART FIFO buffer at first, and turn Tx interrupts only if necessary */
			while (ES_TXINTENI(ensoniq->uartc) == 1 &&
			       (inb(ES_REG(ensoniq, UART_STATUS)) & ES_TXRDY)) {
				if (snd_rawmidi_transmit(substream, &byte, 1) != 1) {
					ensoniq->uartc &= ~ES_TXINTENM;
				} else {
					outb(byte, ES_REG(ensoniq, UART_DATA));
				}
			}
			outb(ensoniq->uartc, ES_REG(ensoniq, UART_CONTROL));
		}
	} else {
		if (ES_TXINTENI(ensoniq->uartc) == 1) {
			ensoniq->uartc &= ~ES_TXINTENM;
			outb(ensoniq->uartc, ES_REG(ensoniq, UART_CONTROL));
		}
	}
	spin_unlock_irqrestore(&ensoniq->reg_lock, flags);
}
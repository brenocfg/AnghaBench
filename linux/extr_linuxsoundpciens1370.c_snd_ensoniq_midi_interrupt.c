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
struct snd_rawmidi {int dummy; } ;
struct ensoniq {int uartm; unsigned char uartc; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  midi_output; int /*<<< orphan*/  midi_input; struct snd_rawmidi* rmidi; } ;

/* Variables and functions */
 int ES_MODE_INPUT ; 
 int ES_MODE_OUTPUT ; 
 int /*<<< orphan*/  ES_REG (struct ensoniq*,int /*<<< orphan*/ ) ; 
 unsigned char ES_RXRDY ; 
 unsigned char ES_TXINTENM ; 
 unsigned char ES_TXRDY ; 
 int /*<<< orphan*/  UART_CONTROL ; 
 int /*<<< orphan*/  UART_DATA ; 
 int /*<<< orphan*/  UART_STATUS ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int snd_rawmidi_transmit (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_ensoniq_midi_interrupt(struct ensoniq * ensoniq)
{
	struct snd_rawmidi *rmidi = ensoniq->rmidi;
	unsigned char status, mask, byte;

	if (rmidi == NULL)
		return;
	/* do Rx at first */
	spin_lock(&ensoniq->reg_lock);
	mask = ensoniq->uartm & ES_MODE_INPUT ? ES_RXRDY : 0;
	while (mask) {
		status = inb(ES_REG(ensoniq, UART_STATUS));
		if ((status & mask) == 0)
			break;
		byte = inb(ES_REG(ensoniq, UART_DATA));
		snd_rawmidi_receive(ensoniq->midi_input, &byte, 1);
	}
	spin_unlock(&ensoniq->reg_lock);

	/* do Tx at second */
	spin_lock(&ensoniq->reg_lock);
	mask = ensoniq->uartm & ES_MODE_OUTPUT ? ES_TXRDY : 0;
	while (mask) {
		status = inb(ES_REG(ensoniq, UART_STATUS));
		if ((status & mask) == 0)
			break;
		if (snd_rawmidi_transmit(ensoniq->midi_output, &byte, 1) != 1) {
			ensoniq->uartc &= ~ES_TXINTENM;
			outb(ensoniq->uartc, ES_REG(ensoniq, UART_CONTROL));
			mask &= ~ES_TXRDY;
		} else {
			outb(byte, ES_REG(ensoniq, UART_DATA));
		}
	}
	spin_unlock(&ensoniq->reg_lock);
}
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
struct ensoniq {int uartc; int /*<<< orphan*/  reg_lock; } ;
struct TYPE_2__ {struct ensoniq* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ES_REG (struct ensoniq*,int /*<<< orphan*/ ) ; 
 int ES_RXINTEN ; 
 int /*<<< orphan*/  UART_CONTROL ; 
 int /*<<< orphan*/  UART_DATA ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_ensoniq_midi_input_trigger(struct snd_rawmidi_substream *substream, int up)
{
	unsigned long flags;
	struct ensoniq *ensoniq = substream->rmidi->private_data;
	int idx;

	spin_lock_irqsave(&ensoniq->reg_lock, flags);
	if (up) {
		if ((ensoniq->uartc & ES_RXINTEN) == 0) {
			/* empty input FIFO */
			for (idx = 0; idx < 32; idx++)
				inb(ES_REG(ensoniq, UART_DATA));
			ensoniq->uartc |= ES_RXINTEN;
			outb(ensoniq->uartc, ES_REG(ensoniq, UART_CONTROL));
		}
	} else {
		if (ensoniq->uartc & ES_RXINTEN) {
			ensoniq->uartc &= ~ES_RXINTEN;
			outb(ensoniq->uartc, ES_REG(ensoniq, UART_CONTROL));
		}
	}
	spin_unlock_irqrestore(&ensoniq->reg_lock, flags);
}
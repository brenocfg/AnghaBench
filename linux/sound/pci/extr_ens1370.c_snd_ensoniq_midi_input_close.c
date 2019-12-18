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
struct ensoniq {int uartm; int uartc; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/ * midi_input; int /*<<< orphan*/  ctrl; } ;
struct TYPE_2__ {struct ensoniq* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL ; 
 int ES_MODE_INPUT ; 
 int ES_MODE_OUTPUT ; 
 int /*<<< orphan*/  ES_REG (struct ensoniq*,int /*<<< orphan*/ ) ; 
 int ES_RXINTEN ; 
 int /*<<< orphan*/  ES_UART_EN ; 
 int /*<<< orphan*/  UART_CONTROL ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ensoniq_midi_input_close(struct snd_rawmidi_substream *substream)
{
	struct ensoniq *ensoniq = substream->rmidi->private_data;

	spin_lock_irq(&ensoniq->reg_lock);
	if (!(ensoniq->uartm & ES_MODE_OUTPUT)) {
		outb(ensoniq->uartc = 0, ES_REG(ensoniq, UART_CONTROL));
		outl(ensoniq->ctrl &= ~ES_UART_EN, ES_REG(ensoniq, CONTROL));
	} else {
		outb(ensoniq->uartc &= ~ES_RXINTEN, ES_REG(ensoniq, UART_CONTROL));
	}
	ensoniq->midi_input = NULL;
	ensoniq->uartm &= ~ES_MODE_INPUT;
	spin_unlock_irq(&ensoniq->reg_lock);
	return 0;
}
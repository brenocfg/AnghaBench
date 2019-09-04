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
struct snd_uart16550 {scalar_t__ filemode; int /*<<< orphan*/  open_lock; int /*<<< orphan*/ ** midi_output; } ;
struct snd_rawmidi_substream {size_t number; TYPE_1__* rmidi; } ;
struct TYPE_2__ {struct snd_uart16550* private_data; } ;

/* Variables and functions */
 scalar_t__ SERIAL_MODE_NOT_OPENED ; 
 scalar_t__ SERIAL_MODE_OUTPUT_OPEN ; 
 int /*<<< orphan*/  snd_uart16550_do_close (struct snd_uart16550*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_uart16550_output_close(struct snd_rawmidi_substream *substream)
{
	unsigned long flags;
	struct snd_uart16550 *uart = substream->rmidi->private_data;

	spin_lock_irqsave(&uart->open_lock, flags);
	uart->filemode &= ~SERIAL_MODE_OUTPUT_OPEN;
	uart->midi_output[substream->number] = NULL;
	if (uart->filemode == SERIAL_MODE_NOT_OPENED)
		snd_uart16550_do_close(uart);
	spin_unlock_irqrestore(&uart->open_lock, flags);
	return 0;
}
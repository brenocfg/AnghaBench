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
struct TYPE_4__ {int uart_cmd; int /*<<< orphan*/  interrupt_handler_midi_out; } ;
struct snd_gus_card {int /*<<< orphan*/  uart_cmd_lock; struct snd_rawmidi_substream* midi_substream_output; TYPE_2__ gf1; } ;
struct TYPE_3__ {struct snd_gus_card* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_gf1_interrupt_midi_out ; 
 int /*<<< orphan*/  snd_gf1_uart_reset (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_gf1_uart_output_open(struct snd_rawmidi_substream *substream)
{
	unsigned long flags;
	struct snd_gus_card *gus;

	gus = substream->rmidi->private_data;
	spin_lock_irqsave(&gus->uart_cmd_lock, flags);
	if (!(gus->gf1.uart_cmd & 0x80)) {	/* input active? */
		snd_gf1_uart_reset(gus, 0);
	}
	gus->gf1.interrupt_handler_midi_out = snd_gf1_interrupt_midi_out;
	gus->midi_substream_output = substream;
	spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
#if 0
	snd_printk(KERN_DEBUG "write init - cmd = 0x%x, stat = 0x%x\n", gus->gf1.uart_cmd, snd_gf1_uart_stat(gus));
#endif
	return 0;
}
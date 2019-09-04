#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {scalar_t__ port_tts; } ;
struct TYPE_4__ {int /*<<< orphan*/  read_buff_add; } ;

/* Variables and functions */
 scalar_t__ UART_IER ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_3__* serstate ; 
 TYPE_2__ speakup_info ; 
 TYPE_1__* synth ; 
 scalar_t__ synth_readbuf_handler ; 

void spk_stop_serial_interrupt(void)
{
	if (speakup_info.port_tts == 0)
		return;

	if (!synth->read_buff_add)
		return;

	/* Turn off interrupts */
	outb(0, speakup_info.port_tts + UART_IER);
	/* Free IRQ */
	free_irq(serstate->irq, (void *)synth_readbuf_handler);
}
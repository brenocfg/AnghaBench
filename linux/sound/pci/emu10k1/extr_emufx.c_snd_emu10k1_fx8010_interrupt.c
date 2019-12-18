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
struct snd_emu10k1_fx8010_irq {scalar_t__ gpr_running; int /*<<< orphan*/  private_data; int /*<<< orphan*/  (* handler ) (struct snd_emu10k1*,int /*<<< orphan*/ ) ;struct snd_emu10k1_fx8010_irq* next; } ;
struct TYPE_2__ {struct snd_emu10k1_fx8010_irq* irq_handlers; } ;
struct snd_emu10k1 {scalar_t__ gpr_base; TYPE_1__ fx8010; } ;

/* Variables and functions */
 int snd_emu10k1_ptr_read (struct snd_emu10k1*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct snd_emu10k1*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_emu10k1_fx8010_interrupt(struct snd_emu10k1 *emu)
{
	struct snd_emu10k1_fx8010_irq *irq, *nirq;

	irq = emu->fx8010.irq_handlers;
	while (irq) {
		nirq = irq->next;	/* irq ptr can be removed from list */
		if (snd_emu10k1_ptr_read(emu, emu->gpr_base + irq->gpr_running, 0) & 0xffff0000) {
			if (irq->handler)
				irq->handler(emu, irq->private_data);
			snd_emu10k1_ptr_write(emu, emu->gpr_base + irq->gpr_running, 0, 1);
		}
		irq = nirq;
	}
}
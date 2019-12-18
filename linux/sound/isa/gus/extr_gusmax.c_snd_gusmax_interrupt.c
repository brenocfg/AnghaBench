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
struct snd_gusmax {int /*<<< orphan*/  wss; int /*<<< orphan*/  pcm_status_reg; int /*<<< orphan*/  gus; int /*<<< orphan*/  gus_status_reg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_gus_interrupt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_wss_interrupt (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t snd_gusmax_interrupt(int irq, void *dev_id)
{
	struct snd_gusmax *maxcard = dev_id;
	int loop, max = 5;
	int handled = 0;

	do {
		loop = 0;
		if (inb(maxcard->gus_status_reg)) {
			handled = 1;
			snd_gus_interrupt(irq, maxcard->gus);
			loop++;
		}
		if (inb(maxcard->pcm_status_reg) & 0x01) { /* IRQ bit is set? */
			handled = 1;
			snd_wss_interrupt(irq, maxcard->wss);
			loop++;
		}
	} while (loop && --max > 0);
	return IRQ_RETVAL(handled);
}
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
struct vx_core {int chip_status; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int VX_STAT_CHIP_INIT ; 
 int VX_STAT_IS_STALE ; 
 int /*<<< orphan*/  vx_test_and_ack (struct vx_core*) ; 

irqreturn_t snd_vx_irq_handler(int irq, void *dev)
{
	struct vx_core *chip = dev;

	if (! (chip->chip_status & VX_STAT_CHIP_INIT) ||
	    (chip->chip_status & VX_STAT_IS_STALE))
		return IRQ_NONE;
	if (! vx_test_and_ack(chip))
		return IRQ_WAKE_THREAD;
	return IRQ_NONE;
}
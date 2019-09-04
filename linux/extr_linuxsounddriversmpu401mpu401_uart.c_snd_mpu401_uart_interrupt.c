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
struct snd_mpu401 {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  _snd_mpu401_uart_interrupt (struct snd_mpu401*) ; 

irqreturn_t snd_mpu401_uart_interrupt(int irq, void *dev_id)
{
	struct snd_mpu401 *mpu = dev_id;
	
	if (!mpu)
		return IRQ_NONE;
	_snd_mpu401_uart_interrupt(mpu);
	return IRQ_HANDLED;
}
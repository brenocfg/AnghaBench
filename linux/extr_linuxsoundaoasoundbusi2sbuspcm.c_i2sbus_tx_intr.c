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
struct i2sbus_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  handle_interrupt (struct i2sbus_dev*,int /*<<< orphan*/ ) ; 

irqreturn_t i2sbus_tx_intr(int irq, void *devid)
{
	handle_interrupt((struct i2sbus_dev *)devid, 0);
	return IRQ_HANDLED;
}
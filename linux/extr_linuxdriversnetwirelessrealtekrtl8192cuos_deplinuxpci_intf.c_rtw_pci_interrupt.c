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
struct pt_regs {int dummy; } ;
struct dvobj_priv {scalar_t__ irq_enabled; int /*<<< orphan*/ * if1; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ _FAIL ; 
 scalar_t__ rtw_hal_interrupt_handler (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rtw_pci_interrupt(int irq, void *priv, struct pt_regs *regs)
{
	struct dvobj_priv *dvobj = (struct dvobj_priv *)priv;
	_adapter *adapter = dvobj->if1;

	if (dvobj->irq_enabled == 0) {
		return IRQ_HANDLED;
	}

	if(rtw_hal_interrupt_handler(adapter) == _FAIL)
		return IRQ_HANDLED;
		//return IRQ_NONE;

	return IRQ_HANDLED;
}
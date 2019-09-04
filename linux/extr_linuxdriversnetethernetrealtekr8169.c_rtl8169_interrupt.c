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
typedef  int u16 ;
struct rtl8169_private {int event_slow; int /*<<< orphan*/  napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RTL_EVENT_NAPI ; 
 int /*<<< orphan*/  napi_schedule_irqoff (int /*<<< orphan*/ *) ; 
 int rtl_get_events (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_irq_disable (struct rtl8169_private*) ; 

__attribute__((used)) static irqreturn_t rtl8169_interrupt(int irq, void *dev_instance)
{
	struct rtl8169_private *tp = dev_instance;
	u16 status = rtl_get_events(tp);

	if (status == 0xffff || !(status & (RTL_EVENT_NAPI | tp->event_slow)))
		return IRQ_NONE;

	rtl_irq_disable(tp);
	napi_schedule_irqoff(&tp->napi);

	return IRQ_HANDLED;
}
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
typedef  int u8 ;
typedef  int u32 ;
struct nbu2ss_udc {int /*<<< orphan*/  lock; struct fc_regs* p_regs; } ;
struct fc_regs {int /*<<< orphan*/  USB_INT_STA; int /*<<< orphan*/  USB_INT_ENA; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EPN_INT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int NUM_ENDPOINTS ; 
 int RSUM_INT ; 
 int SPND_INT ; 
 int USB_INT_STA_RW ; 
 int USB_RST_INT ; 
 int /*<<< orphan*/  VBUS_VALUE ; 
 int /*<<< orphan*/  _nbu2ss_ep_int (struct nbu2ss_udc*,int) ; 
 int /*<<< orphan*/  _nbu2ss_int_bus_reset (struct nbu2ss_udc*) ; 
 int /*<<< orphan*/  _nbu2ss_int_usb_resume (struct nbu2ss_udc*) ; 
 int /*<<< orphan*/  _nbu2ss_int_usb_suspend (struct nbu2ss_udc*) ; 
 int _nbu2ss_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _nbu2ss_writel (int /*<<< orphan*/ *,int) ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t _nbu2ss_udc_irq(int irq, void *_udc)
{
	u8	suspend_flag = 0;
	u32	status;
	u32	epnum, int_bit;

	struct nbu2ss_udc	*udc = (struct nbu2ss_udc *)_udc;
	struct fc_regs	*preg = udc->p_regs;

	if (gpio_get_value(VBUS_VALUE) == 0) {
		_nbu2ss_writel(&preg->USB_INT_STA, ~USB_INT_STA_RW);
		_nbu2ss_writel(&preg->USB_INT_ENA, 0);
		return IRQ_HANDLED;
	}

	spin_lock(&udc->lock);

	for (;;) {
		if (gpio_get_value(VBUS_VALUE) == 0) {
			_nbu2ss_writel(&preg->USB_INT_STA, ~USB_INT_STA_RW);
			_nbu2ss_writel(&preg->USB_INT_ENA, 0);
			status = 0;
		} else {
			status = _nbu2ss_readl(&preg->USB_INT_STA);
		}

		if (status == 0)
			break;

		_nbu2ss_writel(&preg->USB_INT_STA, ~(status & USB_INT_STA_RW));

		if (status & USB_RST_INT) {
			/* USB Reset */
			_nbu2ss_int_bus_reset(udc);
		}

		if (status & RSUM_INT) {
			/* Resume */
			_nbu2ss_int_usb_resume(udc);
		}

		if (status & SPND_INT) {
			/* Suspend */
			suspend_flag = 1;
		}

		if (status & EPN_INT) {
			/* EP INT */
			int_bit = status >> 8;

			for (epnum = 0; epnum < NUM_ENDPOINTS; epnum++) {
				if (0x01 & int_bit)
					_nbu2ss_ep_int(udc, epnum);

				int_bit >>= 1;

				if (int_bit == 0)
					break;
			}
		}
	}

	if (suspend_flag)
		_nbu2ss_int_usb_suspend(udc);

	spin_unlock(&udc->lock);

	return IRQ_HANDLED;
}
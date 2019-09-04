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
struct usba_udc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  USBA_ENABLE_MASK ; 
 int /*<<< orphan*/  USBA_END_OF_RESET ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int start_clock (struct usba_udc*) ; 
 int /*<<< orphan*/  toggle_bias (struct usba_udc*,int) ; 
 int /*<<< orphan*/  usba_int_enb_set (struct usba_udc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usba_writel (struct usba_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usba_start(struct usba_udc *udc)
{
	unsigned long flags;
	int ret;

	ret = start_clock(udc);
	if (ret)
		return ret;

	spin_lock_irqsave(&udc->lock, flags);
	toggle_bias(udc, 1);
	usba_writel(udc, CTRL, USBA_ENABLE_MASK);
	usba_int_enb_set(udc, USBA_END_OF_RESET);
	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;
}
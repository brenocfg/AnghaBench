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
struct usb_gadget {int dummy; } ;
struct m66592 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  M66592_DPRPU ; 
 int /*<<< orphan*/  M66592_SYSCFG ; 
 struct m66592* gadget_to_m66592 (struct usb_gadget*) ; 
 int /*<<< orphan*/  m66592_bclr (struct m66592*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m66592_bset (struct m66592*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int m66592_pullup(struct usb_gadget *gadget, int is_on)
{
	struct m66592 *m66592 = gadget_to_m66592(gadget);
	unsigned long flags;

	spin_lock_irqsave(&m66592->lock, flags);
	if (is_on)
		m66592_bset(m66592, M66592_DPRPU, M66592_SYSCFG);
	else
		m66592_bclr(m66592, M66592_DPRPU, M66592_SYSCFG);
	spin_unlock_irqrestore(&m66592->lock, flags);

	return 0;
}
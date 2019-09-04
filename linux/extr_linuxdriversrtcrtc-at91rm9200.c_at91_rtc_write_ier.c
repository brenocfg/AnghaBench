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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_RTC_IER ; 
 int /*<<< orphan*/  at91_rtc_lock ; 
 int /*<<< orphan*/  at91_rtc_shadow_imr ; 
 int /*<<< orphan*/  at91_rtc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void at91_rtc_write_ier(u32 mask)
{
	unsigned long flags;

	spin_lock_irqsave(&at91_rtc_lock, flags);
	at91_rtc_shadow_imr |= mask;
	at91_rtc_write(AT91_RTC_IER, mask);
	spin_unlock_irqrestore(&at91_rtc_lock, flags);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ use_shadow_imr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_RTC_IMR ; 
 TYPE_1__* at91_rtc_config ; 
 int /*<<< orphan*/  at91_rtc_lock ; 
 int /*<<< orphan*/  at91_rtc_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_rtc_shadow_imr ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u32 at91_rtc_read_imr(void)
{
	unsigned long flags;
	u32 mask;

	if (at91_rtc_config->use_shadow_imr) {
		spin_lock_irqsave(&at91_rtc_lock, flags);
		mask = at91_rtc_shadow_imr;
		spin_unlock_irqrestore(&at91_rtc_lock, flags);
	} else {
		mask = at91_rtc_read(AT91_RTC_IMR);
	}

	return mask;
}
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
struct ds1685_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ds1685_rtc_switch_to_bank0 (struct ds1685_priv*) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void
ds1685_rtc_end_ctrl_access(struct ds1685_priv *rtc, unsigned long flags)
{
	ds1685_rtc_switch_to_bank0(rtc);
	spin_unlock_irqrestore(&rtc->lock, flags);
}
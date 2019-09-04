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
struct rtc7301_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC7301_TIMER_CONTROL ; 
 int /*<<< orphan*/  rtc7301_select_bank (struct rtc7301_priv*,int) ; 
 int /*<<< orphan*/  rtc7301_write (struct rtc7301_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rtc7301_init(struct rtc7301_priv *priv)
{
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);

	rtc7301_select_bank(priv, 2);
	rtc7301_write(priv, 0, RTC7301_TIMER_CONTROL);

	spin_unlock_irqrestore(&priv->lock, flags);
}
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
typedef  int uint32_t ;
struct jz4740_rtc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  JZ_REG_RTC_CTRL ; 
 int JZ_RTC_CTRL_1HZ ; 
 int JZ_RTC_CTRL_AF ; 
 int jz4740_rtc_reg_read (struct jz4740_rtc*,int /*<<< orphan*/ ) ; 
 int jz4740_rtc_reg_write (struct jz4740_rtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int jz4740_rtc_ctrl_set_bits(struct jz4740_rtc *rtc, uint32_t mask,
	bool set)
{
	int ret;
	unsigned long flags;
	uint32_t ctrl;

	spin_lock_irqsave(&rtc->lock, flags);

	ctrl = jz4740_rtc_reg_read(rtc, JZ_REG_RTC_CTRL);

	/* Don't clear interrupt flags by accident */
	ctrl |= JZ_RTC_CTRL_1HZ | JZ_RTC_CTRL_AF;

	if (set)
		ctrl |= mask;
	else
		ctrl &= ~mask;

	ret = jz4740_rtc_reg_write(rtc, JZ_REG_RTC_CTRL, ctrl);

	spin_unlock_irqrestore(&rtc->lock, flags);

	return ret;
}
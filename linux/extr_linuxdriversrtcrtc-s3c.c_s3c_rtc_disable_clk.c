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
struct s3c_rtc {int clk_disabled; int /*<<< orphan*/  alarm_clk_lock; int /*<<< orphan*/  rtc_clk; int /*<<< orphan*/  rtc_src_clk; TYPE_1__* data; } ;
struct TYPE_2__ {scalar_t__ needs_src_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void s3c_rtc_disable_clk(struct s3c_rtc *info)
{
	unsigned long irq_flags;

	spin_lock_irqsave(&info->alarm_clk_lock, irq_flags);
	if (!info->clk_disabled) {
		if (info->data->needs_src_clk)
			clk_disable(info->rtc_src_clk);
		clk_disable(info->rtc_clk);
		info->clk_disabled = true;
	}
	spin_unlock_irqrestore(&info->alarm_clk_lock, irq_flags);
}
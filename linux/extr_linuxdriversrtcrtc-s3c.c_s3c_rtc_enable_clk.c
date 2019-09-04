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
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int s3c_rtc_enable_clk(struct s3c_rtc *info)
{
	unsigned long irq_flags;
	int ret = 0;

	spin_lock_irqsave(&info->alarm_clk_lock, irq_flags);

	if (info->clk_disabled) {
		ret = clk_enable(info->rtc_clk);
		if (ret)
			goto out;

		if (info->data->needs_src_clk) {
			ret = clk_enable(info->rtc_src_clk);
			if (ret) {
				clk_disable(info->rtc_clk);
				goto out;
			}
		}
		info->clk_disabled = false;
	}

out:
	spin_unlock_irqrestore(&info->alarm_clk_lock, irq_flags);

	return ret;
}
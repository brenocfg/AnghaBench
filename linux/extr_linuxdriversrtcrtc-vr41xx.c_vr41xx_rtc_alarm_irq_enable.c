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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aie_irq ; 
 int alarm_enabled ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vr41xx_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	spin_lock_irq(&rtc_lock);
	if (enabled) {
		if (!alarm_enabled) {
			enable_irq(aie_irq);
			alarm_enabled = 1;
		}
	} else {
		if (alarm_enabled) {
			disable_irq(aie_irq);
			alarm_enabled = 0;
		}
	}
	spin_unlock_irq(&rtc_lock);
	return 0;
}
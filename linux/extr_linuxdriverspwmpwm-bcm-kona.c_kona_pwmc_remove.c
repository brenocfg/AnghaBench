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
struct platform_device {int dummy; } ;
struct TYPE_2__ {unsigned int npwm; int /*<<< orphan*/ * pwms; } ;
struct kona_pwmc {TYPE_1__ chip; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct kona_pwmc* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ pwm_is_enabled (int /*<<< orphan*/ *) ; 
 int pwmchip_remove (TYPE_1__*) ; 

__attribute__((used)) static int kona_pwmc_remove(struct platform_device *pdev)
{
	struct kona_pwmc *kp = platform_get_drvdata(pdev);
	unsigned int chan;

	for (chan = 0; chan < kp->chip.npwm; chan++)
		if (pwm_is_enabled(&kp->chip.pwms[chan]))
			clk_disable_unprepare(kp->clk);

	return pwmchip_remove(&kp->chip);
}
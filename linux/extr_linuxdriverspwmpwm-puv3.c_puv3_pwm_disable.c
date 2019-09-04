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
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;
struct puv3_pwm_chip {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct puv3_pwm_chip* to_puv3 (struct pwm_chip*) ; 

__attribute__((used)) static void puv3_pwm_disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct puv3_pwm_chip *puv3 = to_puv3(chip);

	clk_disable_unprepare(puv3->clk);
}
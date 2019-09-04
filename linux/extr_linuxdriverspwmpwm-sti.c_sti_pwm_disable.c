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
struct sti_pwm_chip {int /*<<< orphan*/  sti_pwm_lock; int /*<<< orphan*/  cpt_clk; int /*<<< orphan*/  pwm_clk; int /*<<< orphan*/  pwm_out_en; scalar_t__ en_count; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_field_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sti_pwm_chip* to_sti_pwmchip (struct pwm_chip*) ; 

__attribute__((used)) static void sti_pwm_disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct sti_pwm_chip *pc = to_sti_pwmchip(chip);

	mutex_lock(&pc->sti_pwm_lock);

	if (--pc->en_count) {
		mutex_unlock(&pc->sti_pwm_lock);
		return;
	}

	regmap_field_write(pc->pwm_out_en, 0);

	clk_disable(pc->pwm_clk);
	clk_disable(pc->cpt_clk);

	mutex_unlock(&pc->sti_pwm_lock);
}
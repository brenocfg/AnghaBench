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
typedef  int /*<<< orphan*/  u32 ;
struct vt8500_chip {int /*<<< orphan*/  clk; scalar_t__ base; } ;
struct pwm_device {int /*<<< orphan*/  hwpwm; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_ENABLE ; 
 scalar_t__ REG_CTRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_CTRL_UPDATE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_busy_wait (struct vt8500_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct vt8500_chip* to_vt8500_chip (struct pwm_chip*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vt8500_pwm_disable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct vt8500_chip *vt8500 = to_vt8500_chip(chip);
	u32 val;

	val = readl(vt8500->base + REG_CTRL(pwm->hwpwm));
	val &= ~CTRL_ENABLE;
	writel(val, vt8500->base + REG_CTRL(pwm->hwpwm));
	pwm_busy_wait(vt8500, pwm->hwpwm, STATUS_CTRL_UPDATE);

	clk_disable(vt8500->clk);
}
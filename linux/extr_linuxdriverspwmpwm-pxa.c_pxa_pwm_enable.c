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
struct pxa_pwm_chip {int /*<<< orphan*/  clk; } ;
struct pwm_device {int dummy; } ;
struct pwm_chip {int dummy; } ;

/* Variables and functions */
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct pxa_pwm_chip* to_pxa_pwm_chip (struct pwm_chip*) ; 

__attribute__((used)) static int pxa_pwm_enable(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct pxa_pwm_chip *pc = to_pxa_pwm_chip(chip);

	return clk_prepare_enable(pc->clk);
}
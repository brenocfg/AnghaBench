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
typedef  int u32 ;
struct fsl_pwm_chip {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTM_MOD ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned long fsl_pwm_calculate_duty(struct fsl_pwm_chip *fpc,
					    unsigned long period_ns,
					    unsigned long duty_ns)
{
	unsigned long long duty;
	u32 val;

	regmap_read(fpc->regmap, FTM_MOD, &val);
	duty = (unsigned long long)duty_ns * (val + 1);
	do_div(duty, period_ns);

	return (unsigned long)duty;
}
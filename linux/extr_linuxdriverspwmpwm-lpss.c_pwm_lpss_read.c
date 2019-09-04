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
struct pwm_lpss_chip {scalar_t__ regs; } ;
struct pwm_device {int hwpwm; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 scalar_t__ PWM ; 
 int PWM_SIZE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct pwm_lpss_chip* to_lpwm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 pwm_lpss_read(const struct pwm_device *pwm)
{
	struct pwm_lpss_chip *lpwm = to_lpwm(pwm->chip);

	return readl(lpwm->regs + pwm->hwpwm * PWM_SIZE + PWM);
}
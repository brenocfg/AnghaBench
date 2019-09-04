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
struct pwm_chip {int /*<<< orphan*/  dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ep93xx_pwm_release_gpio (struct platform_device*) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep93xx_pwm_free(struct pwm_chip *chip, struct pwm_device *pwm)
{
	struct platform_device *pdev = to_platform_device(chip->dev);

	ep93xx_pwm_release_gpio(pdev);
}
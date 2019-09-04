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
struct ab8500_charger {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_CHARGER ; 
 int /*<<< orphan*/  AB8500_LED_INDICATOR_PWM_CTRL ; 
 int /*<<< orphan*/  AB8500_LED_INDICATOR_PWM_DUTY ; 
 int LED_INDICATOR_PWM_DIS ; 
 int LED_INDICATOR_PWM_DUTY_252_256 ; 
 int LED_INDICATOR_PWM_ENA ; 
 int LED_IND_CUR_5MA ; 
 int abx500_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ab8500_charger_led_en(struct ab8500_charger *di, int on)
{
	int ret;

	if (on) {
		/* Power ON charging LED indicator, set LED current to 5mA */
		ret = abx500_set_register_interruptible(di->dev, AB8500_CHARGER,
			AB8500_LED_INDICATOR_PWM_CTRL,
			(LED_IND_CUR_5MA | LED_INDICATOR_PWM_ENA));
		if (ret) {
			dev_err(di->dev, "Power ON LED failed\n");
			return ret;
		}
		/* LED indicator PWM duty cycle 252/256 */
		ret = abx500_set_register_interruptible(di->dev, AB8500_CHARGER,
			AB8500_LED_INDICATOR_PWM_DUTY,
			LED_INDICATOR_PWM_DUTY_252_256);
		if (ret) {
			dev_err(di->dev, "Set LED PWM duty cycle failed\n");
			return ret;
		}
	} else {
		/* Power off charging LED indicator */
		ret = abx500_set_register_interruptible(di->dev, AB8500_CHARGER,
			AB8500_LED_INDICATOR_PWM_CTRL,
			LED_INDICATOR_PWM_DIS);
		if (ret) {
			dev_err(di->dev, "Power-off LED failed\n");
			return ret;
		}
	}

	return ret;
}
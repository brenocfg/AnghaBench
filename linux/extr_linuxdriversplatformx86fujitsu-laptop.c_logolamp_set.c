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
struct led_classdev {TYPE_1__* dev; } ;
struct acpi_device {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC_LEDS ; 
 int FUNC_LED_OFF ; 
 int FUNC_LED_ON ; 
 int LED_FULL ; 
 int LED_HALF ; 
 int /*<<< orphan*/  LOGOLAMP_ALWAYS ; 
 int /*<<< orphan*/  LOGOLAMP_POWERON ; 
 int call_fext_func (struct acpi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct acpi_device* to_acpi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int logolamp_set(struct led_classdev *cdev,
			enum led_brightness brightness)
{
	struct acpi_device *device = to_acpi_device(cdev->dev->parent);
	int poweron = FUNC_LED_ON, always = FUNC_LED_ON;
	int ret;

	if (brightness < LED_HALF)
		poweron = FUNC_LED_OFF;

	if (brightness < LED_FULL)
		always = FUNC_LED_OFF;

	ret = call_fext_func(device, FUNC_LEDS, 0x1, LOGOLAMP_POWERON, poweron);
	if (ret < 0)
		return ret;

	return call_fext_func(device, FUNC_LEDS, 0x1, LOGOLAMP_ALWAYS, always);
}
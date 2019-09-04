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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct led_classdev {char* name; int /*<<< orphan*/  brightness_get; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  flags; int /*<<< orphan*/  max_brightness; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_KEYBOARD_BACKLIGHT_DEVICE ; 
 int /*<<< orphan*/  ACPI_KEYBOARD_BACKLIGHT_MAX ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LED_CORE_SUSPENDRESUME ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct led_classdev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_led_classdev_register (int /*<<< orphan*/ *,struct led_classdev*) ; 
 int /*<<< orphan*/  keyboard_led_get_brightness ; 
 int /*<<< orphan*/  keyboard_led_set_brightness ; 

__attribute__((used)) static int keyboard_led_probe(struct platform_device *pdev)
{
	struct led_classdev *cdev;
	acpi_handle handle;
	acpi_status status;
	int error;

	/* Look for the keyboard LED ACPI Device */
	status = acpi_get_handle(ACPI_ROOT_OBJECT,
				 ACPI_KEYBOARD_BACKLIGHT_DEVICE,
				 &handle);
	if (ACPI_FAILURE(status)) {
		dev_err(&pdev->dev, "Unable to find ACPI device %s: %d\n",
			ACPI_KEYBOARD_BACKLIGHT_DEVICE, status);
		return -ENXIO;
	}

	cdev = devm_kzalloc(&pdev->dev, sizeof(*cdev), GFP_KERNEL);
	if (!cdev)
		return -ENOMEM;

	cdev->name = "chromeos::kbd_backlight";
	cdev->max_brightness = ACPI_KEYBOARD_BACKLIGHT_MAX;
	cdev->flags |= LED_CORE_SUSPENDRESUME;
	cdev->brightness_set = keyboard_led_set_brightness;
	cdev->brightness_get = keyboard_led_get_brightness;

	error = devm_led_classdev_register(&pdev->dev, cdev);
	if (error)
		return error;

	return 0;
}
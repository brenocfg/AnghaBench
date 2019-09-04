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
struct platform_device_id {scalar_t__ driver_data; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
typedef  struct atmel_pwm_registers const atmel_pwm_registers ;

/* Variables and functions */
 struct atmel_pwm_registers const* of_device_get_match_data (TYPE_1__*) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 

__attribute__((used)) static inline const struct atmel_pwm_registers *
atmel_pwm_get_driver_data(struct platform_device *pdev)
{
	const struct platform_device_id *id;

	if (pdev->dev.of_node)
		return of_device_get_match_data(&pdev->dev);

	id = platform_get_device_id(pdev);

	return (struct atmel_pwm_registers *)id->driver_data;
}
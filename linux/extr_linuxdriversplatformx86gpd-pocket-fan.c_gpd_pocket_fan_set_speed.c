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
struct gpd_pocket_fan_data {int last_speed; int /*<<< orphan*/  gpio1; int /*<<< orphan*/  gpio0; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gpd_pocket_fan_set_speed(struct gpd_pocket_fan_data *fan, int speed)
{
	if (speed == fan->last_speed)
		return;

	gpiod_direction_output(fan->gpio0, !!(speed & 1));
	gpiod_direction_output(fan->gpio1, !!(speed & 2));

	fan->last_speed = speed;
}
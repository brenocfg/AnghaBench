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
typedef  int uint8_t ;
struct backlight_device {int dummy; } ;
struct adp5520_bl {int current_brightness; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADP5520_BL_VALUE ; 
 int adp5520_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct adp5520_bl* bl_get_data (struct backlight_device*) ; 

__attribute__((used)) static int adp5520_bl_get_brightness(struct backlight_device *bl)
{
	struct adp5520_bl *data = bl_get_data(bl);
	int error;
	uint8_t reg_val;

	error = adp5520_read(data->master, ADP5520_BL_VALUE, &reg_val);

	return error ? data->current_brightness : reg_val;
}
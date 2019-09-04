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
struct ds2760_device_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS2760_CURRENT_ACCUM_MSB ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int w1_ds2760_write (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ds2760_battery_set_current_accum(struct ds2760_device_info *di,
					     unsigned int acr_val)
{
	unsigned char acr[2];

	/* acr is in units of 0.25 mAh */
	acr_val *= 4L;
	acr_val /= 1000;

	acr[0] = acr_val >> 8;
	acr[1] = acr_val & 0xff;

	if (w1_ds2760_write(di->dev, acr, DS2760_CURRENT_ACCUM_MSB, 2) < 2)
		dev_warn(di->dev, "ACR write failed\n");
}
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
struct mx3fb_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDC_PWM_CTRL ; 
 int mx3fb_read_reg (struct mx3fb_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 sdc_get_brightness(struct mx3fb_data *mx3fb)
{
	u32 brightness;

	brightness = mx3fb_read_reg(mx3fb, SDC_PWM_CTRL);
	brightness = (brightness >> 16) & 0xFF;

	return brightness;
}
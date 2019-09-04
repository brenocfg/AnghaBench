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
struct TYPE_2__ {int /*<<< orphan*/  bl_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORGIBL_BATTLOW ; 
 int /*<<< orphan*/  backlight_update_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  corgibl_flags ; 
 TYPE_1__* the_corgi_lcd ; 

void corgi_lcd_limit_intensity(int limit)
{
	if (limit)
		corgibl_flags |= CORGIBL_BATTLOW;
	else
		corgibl_flags &= ~CORGIBL_BATTLOW;

	backlight_update_status(the_corgi_lcd->bl_dev);
}
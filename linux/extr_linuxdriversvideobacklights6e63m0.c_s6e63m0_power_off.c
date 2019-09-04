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
struct s6e63m0 {int /*<<< orphan*/  ld; int /*<<< orphan*/  dev; struct lcd_platform_data* lcd_pd; } ;
struct lcd_platform_data {int /*<<< orphan*/  (* power_on ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  power_off_delay; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int s6e63m0_ldi_disable (struct s6e63m0*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s6e63m0_power_off(struct s6e63m0 *lcd)
{
	int ret;
	struct lcd_platform_data *pd;

	pd = lcd->lcd_pd;

	ret = s6e63m0_ldi_disable(lcd);
	if (ret) {
		dev_err(lcd->dev, "lcd setting failed.\n");
		return -EIO;
	}

	msleep(pd->power_off_delay);

	pd->power_on(lcd->ld, 0);

	return 0;
}
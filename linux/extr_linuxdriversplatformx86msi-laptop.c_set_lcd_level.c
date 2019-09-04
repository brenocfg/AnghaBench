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
typedef  int u8 ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MSI_EC_COMMAND_LCD_LEVEL ; 
 int MSI_LCD_LEVEL_MAX ; 
 int ec_transaction (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_lcd_level(int level)
{
	u8 buf[2];

	if (level < 0 || level >= MSI_LCD_LEVEL_MAX)
		return -EINVAL;

	buf[0] = 0x80;
	buf[1] = (u8) (level*31);

	return ec_transaction(MSI_EC_COMMAND_LCD_LEVEL, buf, sizeof(buf),
			      NULL, 0);
}
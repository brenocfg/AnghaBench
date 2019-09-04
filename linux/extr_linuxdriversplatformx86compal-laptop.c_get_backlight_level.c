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

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_LEVEL_ADDR ; 
 scalar_t__ ec_read_u8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_backlight_level(void)
{
	return (int) ec_read_u8(BACKLIGHT_LEVEL_ADDR);
}
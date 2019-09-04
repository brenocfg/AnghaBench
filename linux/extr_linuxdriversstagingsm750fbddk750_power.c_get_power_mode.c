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
 int /*<<< orphan*/  POWER_MODE_CTRL ; 
 unsigned int POWER_MODE_CTRL_MODE_MASK ; 
 scalar_t__ SM750LE ; 
 unsigned int peek32 (int /*<<< orphan*/ ) ; 
 scalar_t__ sm750_get_chip_type () ; 

__attribute__((used)) static unsigned int get_power_mode(void)
{
	if (sm750_get_chip_type() == SM750LE)
		return 0;
	return peek32(POWER_MODE_CTRL) & POWER_MODE_CTRL_MODE_MASK;
}
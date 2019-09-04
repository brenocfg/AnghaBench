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
struct fdp_i2c_phy {int /*<<< orphan*/  power_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDP_POWER_OFF ; 
 int /*<<< orphan*/  FDP_POWER_ON ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void fdp_nci_i2c_reset(struct fdp_i2c_phy *phy)
{
	/* Reset RST/WakeUP for at least 100 micro-second */
	gpiod_set_value_cansleep(phy->power_gpio, FDP_POWER_OFF);
	usleep_range(1000, 4000);
	gpiod_set_value_cansleep(phy->power_gpio, FDP_POWER_ON);
	usleep_range(10000, 14000);
}
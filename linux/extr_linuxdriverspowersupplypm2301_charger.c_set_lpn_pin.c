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
struct TYPE_2__ {int /*<<< orphan*/  charger_connected; } ;
struct pm2xxx_charger {int /*<<< orphan*/  lpn_pin; TYPE_1__ ac; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLEEP_MAX ; 
 int /*<<< orphan*/  SLEEP_MIN ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_lpn_pin(struct pm2xxx_charger *pm2)
{
	if (!pm2->ac.charger_connected && gpio_is_valid(pm2->lpn_pin)) {
		gpio_set_value(pm2->lpn_pin, 1);
		usleep_range(SLEEP_MIN, SLEEP_MAX);
	}
}
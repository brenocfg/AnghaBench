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
struct ak5558_priv {int /*<<< orphan*/  reset_gpiod; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ak5558_power_on(struct ak5558_priv *ak5558)
{
	if (!ak5558->reset_gpiod)
		return;

	gpiod_set_value_cansleep(ak5558->reset_gpiod, 1);
	usleep_range(1000, 2000);
}
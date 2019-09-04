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
struct ak4458_priv {scalar_t__ reset_gpiod; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ak4458_power_off(struct ak4458_priv *ak4458)
{
	if (ak4458->reset_gpiod) {
		gpiod_set_value_cansleep(ak4458->reset_gpiod, 0);
		usleep_range(1000, 2000);
	}
}
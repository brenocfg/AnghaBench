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
struct sta350_priv {scalar_t__ gpiod_nreset; scalar_t__ gpiod_power_down; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int sta350_startup_sequence(struct sta350_priv *sta350)
{
	if (sta350->gpiod_power_down)
		gpiod_set_value(sta350->gpiod_power_down, 1);

	if (sta350->gpiod_nreset) {
		gpiod_set_value(sta350->gpiod_nreset, 0);
		mdelay(1);
		gpiod_set_value(sta350->gpiod_nreset, 1);
		mdelay(1);
	}

	return 0;
}
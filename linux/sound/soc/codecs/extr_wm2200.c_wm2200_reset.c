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
struct TYPE_2__ {scalar_t__ reset; } ;
struct wm2200_priv {int /*<<< orphan*/  regmap; TYPE_1__ pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM2200_SOFTWARE_RESET ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (scalar_t__,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm2200_reset(struct wm2200_priv *wm2200)
{
	if (wm2200->pdata.reset) {
		gpio_set_value_cansleep(wm2200->pdata.reset, 0);
		gpio_set_value_cansleep(wm2200->pdata.reset, 1);

		return 0;
	} else {
		return regmap_write(wm2200->regmap, WM2200_SOFTWARE_RESET,
				    0x2200);
	}
}
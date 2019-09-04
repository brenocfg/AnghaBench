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
struct wm8962_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8962_PLL_SOFTWARE_RESET ; 
 int /*<<< orphan*/  WM8962_SOFTWARE_RESET ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8962_reset(struct wm8962_priv *wm8962)
{
	int ret;

	ret = regmap_write(wm8962->regmap, WM8962_SOFTWARE_RESET, 0x6243);
	if (ret != 0)
		return ret;

	return regmap_write(wm8962->regmap, WM8962_PLL_SOFTWARE_RESET, 0);
}
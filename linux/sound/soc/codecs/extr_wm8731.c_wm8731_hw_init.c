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
struct wm8731_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM8731_APANA ; 
 int /*<<< orphan*/  WM8731_LINVOL ; 
 int /*<<< orphan*/  WM8731_LOUT1V ; 
 int /*<<< orphan*/  WM8731_PWR ; 
 int /*<<< orphan*/  WM8731_RINVOL ; 
 int /*<<< orphan*/  WM8731_ROUT1V ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  regcache_mark_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wm8731_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8731_hw_init(struct device *dev, struct wm8731_priv *wm8731)
{
	int ret = 0;

	ret = wm8731_reset(wm8731->regmap);
	if (ret < 0) {
		dev_err(dev, "Failed to issue reset: %d\n", ret);
		goto err_regulator_enable;
	}

	/* Clear POWEROFF, keep everything else disabled */
	regmap_write(wm8731->regmap, WM8731_PWR, 0x7f);

	/* Latch the update bits */
	regmap_update_bits(wm8731->regmap, WM8731_LOUT1V, 0x100, 0);
	regmap_update_bits(wm8731->regmap, WM8731_ROUT1V, 0x100, 0);
	regmap_update_bits(wm8731->regmap, WM8731_LINVOL, 0x100, 0);
	regmap_update_bits(wm8731->regmap, WM8731_RINVOL, 0x100, 0);

	/* Disable bypass path by default */
	regmap_update_bits(wm8731->regmap, WM8731_APANA, 0x8, 0);

	regcache_mark_dirty(wm8731->regmap);

err_regulator_enable:
	/* Regulators will be enabled by bias management */
	regulator_bulk_disable(ARRAY_SIZE(wm8731->supplies), wm8731->supplies);

	return ret;
}
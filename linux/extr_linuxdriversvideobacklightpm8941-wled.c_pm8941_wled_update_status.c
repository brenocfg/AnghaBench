#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_4__ {int num_strings; } ;
struct pm8941_wled {scalar_t__ addr; int /*<<< orphan*/  regmap; TYPE_2__ cfg; } ;
struct TYPE_3__ {scalar_t__ brightness; scalar_t__ power; scalar_t__ fb_blank; int state; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int BL_CORE_FBBLANK ; 
 scalar_t__ FB_BLANK_UNBLANK ; 
 scalar_t__ PM8941_WLED_REG_MOD_EN ; 
 scalar_t__ PM8941_WLED_REG_MOD_EN_BIT ; 
 int /*<<< orphan*/  PM8941_WLED_REG_MOD_EN_MASK ; 
 scalar_t__ PM8941_WLED_REG_SYNC ; 
 scalar_t__ PM8941_WLED_REG_SYNC_ALL ; 
 scalar_t__ PM8941_WLED_REG_SYNC_CLEAR ; 
 int /*<<< orphan*/  PM8941_WLED_REG_SYNC_MASK ; 
 scalar_t__ PM8941_WLED_REG_VAL_BASE ; 
 struct pm8941_wled* bl_get_data (struct backlight_device*) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pm8941_wled_update_status(struct backlight_device *bl)
{
	struct pm8941_wled *wled = bl_get_data(bl);
	u16 val = bl->props.brightness;
	u8 ctrl = 0;
	int rc;
	int i;

	if (bl->props.power != FB_BLANK_UNBLANK ||
	    bl->props.fb_blank != FB_BLANK_UNBLANK ||
	    bl->props.state & BL_CORE_FBBLANK)
		val = 0;

	if (val != 0)
		ctrl = PM8941_WLED_REG_MOD_EN_BIT;

	rc = regmap_update_bits(wled->regmap,
			wled->addr + PM8941_WLED_REG_MOD_EN,
			PM8941_WLED_REG_MOD_EN_MASK, ctrl);
	if (rc)
		return rc;

	for (i = 0; i < wled->cfg.num_strings; ++i) {
		u8 v[2] = { val & 0xff, (val >> 8) & 0xf };

		rc = regmap_bulk_write(wled->regmap,
				wled->addr + PM8941_WLED_REG_VAL_BASE + 2 * i,
				v, 2);
		if (rc)
			return rc;
	}

	rc = regmap_update_bits(wled->regmap,
			wled->addr + PM8941_WLED_REG_SYNC,
			PM8941_WLED_REG_SYNC_MASK, PM8941_WLED_REG_SYNC_ALL);
	if (rc)
		return rc;

	rc = regmap_update_bits(wled->regmap,
			wled->addr + PM8941_WLED_REG_SYNC,
			PM8941_WLED_REG_SYNC_MASK, PM8941_WLED_REG_SYNC_CLEAR);
	return rc;
}
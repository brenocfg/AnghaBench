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
struct smb347_charger {int /*<<< orphan*/  regmap; TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ usb_hc_current_limit; scalar_t__ mains_current_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG_CURRENT_LIMIT ; 
 int /*<<< orphan*/  CFG_CURRENT_LIMIT_DC_MASK ; 
 int CFG_CURRENT_LIMIT_DC_SHIFT ; 
 int /*<<< orphan*/  CFG_CURRENT_LIMIT_USB_MASK ; 
 int current_to_hw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  icl_tbl ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smb347_set_current_limits(struct smb347_charger *smb)
{
	int ret;

	if (smb->pdata->mains_current_limit) {
		ret = current_to_hw(icl_tbl, ARRAY_SIZE(icl_tbl),
				    smb->pdata->mains_current_limit);
		if (ret < 0)
			return ret;

		ret = regmap_update_bits(smb->regmap, CFG_CURRENT_LIMIT,
					 CFG_CURRENT_LIMIT_DC_MASK,
					 ret << CFG_CURRENT_LIMIT_DC_SHIFT);
		if (ret < 0)
			return ret;
	}

	if (smb->pdata->usb_hc_current_limit) {
		ret = current_to_hw(icl_tbl, ARRAY_SIZE(icl_tbl),
				    smb->pdata->usb_hc_current_limit);
		if (ret < 0)
			return ret;

		ret = regmap_update_bits(smb->regmap, CFG_CURRENT_LIMIT,
					 CFG_CURRENT_LIMIT_USB_MASK, ret);
		if (ret < 0)
			return ret;
	}

	return 0;
}
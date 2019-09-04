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
struct rockchip_usb2phy {TYPE_2__* phy_cfg; } ;
struct regmap {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  idp_src_en; int /*<<< orphan*/  rdm_pdwn_en; } ;
struct TYPE_4__ {TYPE_1__ chg_det; } ;

/* Variables and functions */
 struct regmap* get_reg_base (struct rockchip_usb2phy*) ; 
 int /*<<< orphan*/  property_enable (struct regmap*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void rockchip_chg_enable_dcd(struct rockchip_usb2phy *rphy,
				    bool en)
{
	struct regmap *base = get_reg_base(rphy);

	property_enable(base, &rphy->phy_cfg->chg_det.rdm_pdwn_en, en);
	property_enable(base, &rphy->phy_cfg->chg_det.idp_src_en, en);
}
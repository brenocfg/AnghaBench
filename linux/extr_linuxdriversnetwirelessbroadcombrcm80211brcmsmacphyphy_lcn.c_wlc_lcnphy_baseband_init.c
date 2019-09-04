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
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ LCNREV_IS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_lcnphy_bu_tweaks (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_rev0_baseband_init (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_rev2_baseband_init (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_lcnphy_tbl_init (struct brcms_phy*) ; 

__attribute__((used)) static void wlc_lcnphy_baseband_init(struct brcms_phy *pi)
{

	wlc_lcnphy_tbl_init(pi);
	wlc_lcnphy_rev0_baseband_init(pi);
	if (LCNREV_IS(pi->pubpi.phy_rev, 2))
		wlc_lcnphy_rev2_baseband_init(pi);
	wlc_lcnphy_bu_tweaks(pi);
}
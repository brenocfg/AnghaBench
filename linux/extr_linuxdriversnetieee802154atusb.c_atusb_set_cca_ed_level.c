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
typedef  size_t u32 ;
struct ieee802154_hw {TYPE_2__* phy; struct atusb* priv; } ;
struct atusb {int dummy; } ;
typedef  scalar_t__ s32 ;
struct TYPE_3__ {size_t cca_ed_levels_size; scalar_t__* cca_ed_levels; } ;
struct TYPE_4__ {TYPE_1__ supported; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SR_CCA_ED_THRES ; 
 int atusb_write_subreg (struct atusb*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
atusb_set_cca_ed_level(struct ieee802154_hw *hw, s32 mbm)
{
	struct atusb *atusb = hw->priv;
	u32 i;

	for (i = 0; i < hw->phy->supported.cca_ed_levels_size; i++) {
		if (hw->phy->supported.cca_ed_levels[i] == mbm)
			return atusb_write_subreg(atusb, SR_CCA_ED_THRES, i);
	}

	return -EINVAL;
}
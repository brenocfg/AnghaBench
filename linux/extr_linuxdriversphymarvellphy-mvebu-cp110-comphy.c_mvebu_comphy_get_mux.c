#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;
struct TYPE_3__ {int lane; int port; int mode; int mux; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int PHY_MODE_INVALID ; 
 TYPE_1__* mvebu_comphy_cp110_modes ; 

__attribute__((used)) static int mvebu_comphy_get_mux(int lane, int port, enum phy_mode mode)
{
	int i, n = ARRAY_SIZE(mvebu_comphy_cp110_modes);

	/* Unused PHY mux value is 0x0 */
	if (mode == PHY_MODE_INVALID)
		return 0;

	for (i = 0; i < n; i++) {
		if (mvebu_comphy_cp110_modes[i].lane == lane &&
		    mvebu_comphy_cp110_modes[i].port == port &&
		    mvebu_comphy_cp110_modes[i].mode == mode)
			break;
	}

	if (i == n)
		return -EINVAL;

	return mvebu_comphy_cp110_modes[i].mux;
}
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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct b43legacy_wldev {int dummy; } ;

/* Variables and functions */
 scalar_t__ b43legacy_phy_lo_g_deviation_subval (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 b43legacy_phy_lo_g_singledeviation(struct b43legacy_wldev *dev,
					      u16 control)
{
	int i;
	u32 ret = 0;

	for (i = 0; i < 8; i++)
		ret += b43legacy_phy_lo_g_deviation_subval(dev, control);

	return ret;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct lpphy_tx_gains {int dummy; } ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void lpphy_papd_cal(struct b43_wldev *dev, struct lpphy_tx_gains gains,
			   int mode, bool useindex, u8 index)
{
	//TODO
}
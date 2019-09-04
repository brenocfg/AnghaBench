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
typedef  int u32 ;
struct phy_device {int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  PHY_1000BT_FEATURES ; 
 int /*<<< orphan*/  PHY_100BT_FEATURES ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 

__attribute__((used)) static int __set_phy_supported(struct phy_device *phydev, u32 max_speed)
{
	switch (max_speed) {
	case SPEED_10:
		phydev->supported &= ~PHY_100BT_FEATURES;
		/* fall through */
	case SPEED_100:
		phydev->supported &= ~PHY_1000BT_FEATURES;
		break;
	case SPEED_1000:
		break;
	default:
		return -ENOTSUPP;
	}

	return 0;
}
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
struct phylink {int link_an_mode; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MLO_AN_FIXED 130 
#define  MLO_AN_INBAND 129 
#define  MLO_AN_PHY 128 

__attribute__((used)) static int phylink_mii_write(struct phylink *pl, unsigned int phy_id,
			     unsigned int reg, unsigned int val)
{
	switch (pl->link_an_mode) {
	case MLO_AN_FIXED:
		break;

	case MLO_AN_PHY:
		return -EOPNOTSUPP;

	case MLO_AN_INBAND:
		break;
	}

	return 0;
}
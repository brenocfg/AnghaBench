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
typedef  scalar_t__ u32 ;
struct ave_private {void* pinmode_val; void* pinmode_mask; } ;
typedef  int phy_interface_t ;

/* Variables and functions */
 int EINVAL ; 
#define  PHY_INTERFACE_MODE_RGMII 129 
#define  PHY_INTERFACE_MODE_RMII 128 
 void* SG_ETPINMODE_RMII (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ave_ld20_get_pinmode(struct ave_private *priv,
				phy_interface_t phy_mode, u32 arg)
{
	if (arg > 0)
		return -EINVAL;

	priv->pinmode_mask = SG_ETPINMODE_RMII(0);

	switch (phy_mode) {
	case PHY_INTERFACE_MODE_RMII:
		priv->pinmode_val = SG_ETPINMODE_RMII(0);
		break;
	case PHY_INTERFACE_MODE_RGMII:
		priv->pinmode_val = 0;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
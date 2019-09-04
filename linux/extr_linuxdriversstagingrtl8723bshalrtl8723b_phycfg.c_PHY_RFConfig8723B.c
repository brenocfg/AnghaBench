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
struct adapter {int dummy; } ;

/* Variables and functions */
 int PHY_RF6052_Config8723B (struct adapter*) ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  phy_LCK_8723B (struct adapter*) ; 

int PHY_RFConfig8723B(struct adapter *Adapter)
{
	int rtStatus = _SUCCESS;

	/*  */
	/*  RF config */
	/*  */
	rtStatus = PHY_RF6052_Config8723B(Adapter);

	phy_LCK_8723B(Adapter);
	/* PHY_BB8723B_Config_1T(Adapter); */

	return rtStatus;
}
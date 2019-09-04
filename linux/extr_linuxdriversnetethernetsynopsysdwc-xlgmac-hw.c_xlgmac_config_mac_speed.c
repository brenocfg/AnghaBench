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
struct xlgmac_pdata {int phy_speed; } ;

/* Variables and functions */
#define  SPEED_100000 131 
#define  SPEED_25000 130 
#define  SPEED_40000 129 
#define  SPEED_50000 128 
 int /*<<< orphan*/  xlgmac_set_xlgmii_100000_speed (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_set_xlgmii_25000_speed (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_set_xlgmii_40000_speed (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_set_xlgmii_50000_speed (struct xlgmac_pdata*) ; 

__attribute__((used)) static void xlgmac_config_mac_speed(struct xlgmac_pdata *pdata)
{
	switch (pdata->phy_speed) {
	case SPEED_100000:
		xlgmac_set_xlgmii_100000_speed(pdata);
		break;

	case SPEED_50000:
		xlgmac_set_xlgmii_50000_speed(pdata);
		break;

	case SPEED_40000:
		xlgmac_set_xlgmii_40000_speed(pdata);
		break;

	case SPEED_25000:
		xlgmac_set_xlgmii_25000_speed(pdata);
		break;
	}
}
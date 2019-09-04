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
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  phy_SsPwrSwitch92CU (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rf_off ; 

void _ps_close_RF(_adapter *padapter){
	//here call with bRegSSPwrLvl 1, bRegSSPwrLvl 2 needs to be verified
	phy_SsPwrSwitch92CU(padapter, rf_off, 1);
}
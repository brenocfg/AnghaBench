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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ EFUSE_WIFI ; 
 int /*<<< orphan*/  hal_EfuseGetCurrentSize_BT (struct adapter*,int) ; 
 int /*<<< orphan*/  hal_EfuseGetCurrentSize_WiFi (struct adapter*,int) ; 

__attribute__((used)) static u16 Hal_EfuseGetCurrentSize(
	struct adapter *padapter, u8 efuseType, bool bPseudoTest
)
{
	u16 ret = 0;

	if (efuseType == EFUSE_WIFI)
		ret = hal_EfuseGetCurrentSize_WiFi(padapter, bPseudoTest);
	else
		ret = hal_EfuseGetCurrentSize_BT(padapter, bPseudoTest);

	return ret;
}
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
struct TYPE_3__ {int /*<<< orphan*/  VersionID; } ;
typedef  int /*<<< orphan*/  PADAPTER ;
typedef  TYPE_1__ HAL_DATA_TYPE ;

/* Variables and functions */
 TYPE_1__* GET_HAL_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192c_ReadChipVersion (int /*<<< orphan*/ ) ; 

void rtl8192c_read_chip_version(PADAPTER	pAdapter)
{
	HAL_DATA_TYPE	*pHalData	= GET_HAL_DATA(pAdapter);
	pHalData->VersionID = rtl8192c_ReadChipVersion(pAdapter);
}
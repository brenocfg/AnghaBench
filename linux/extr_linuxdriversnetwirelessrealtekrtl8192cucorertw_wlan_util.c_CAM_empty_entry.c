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
typedef  int /*<<< orphan*/  PADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_CAM_EMPTY_ENTRY ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void CAM_empty_entry(
	PADAPTER     	Adapter,	
	u8 			ucIndex
)
{
	rtw_hal_set_hwreg(Adapter, HW_VAR_CAM_EMPTY_ENTRY, (u8 *)(&ucIndex));
}
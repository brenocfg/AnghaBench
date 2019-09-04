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
 int /*<<< orphan*/  rtw_hal_bcn_related_reg_setting (int /*<<< orphan*/ *) ; 

void beacon_timing_control(_adapter *padapter)
{
	rtw_hal_bcn_related_reg_setting(padapter);
}
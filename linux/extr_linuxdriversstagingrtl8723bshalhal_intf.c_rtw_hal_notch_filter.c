#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* hal_notch_filter ) (struct adapter*,int) ;} ;
struct adapter {TYPE_1__ HalFunc; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct adapter*,int) ; 

void rtw_hal_notch_filter(struct adapter *adapter, bool enable)
{
	if (adapter->HalFunc.hal_notch_filter)
		adapter->HalFunc.hal_notch_filter(adapter, enable);
}
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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  _adapter ;
struct TYPE_2__ {scalar_t__ oper_channel; int /*<<< orphan*/  on_oper_ch_time; } ;

/* Variables and functions */
 TYPE_1__* adapter_to_dvobj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_get_current_time () ; 

inline void rtw_set_oper_ch(_adapter *adapter, u8 ch)
{
	if (adapter_to_dvobj(adapter)->oper_channel != ch)
		adapter_to_dvobj(adapter)->on_oper_ch_time = rtw_get_current_time();

	adapter_to_dvobj(adapter)->oper_channel = ch;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {scalar_t__ cur_channel; } ;
struct TYPE_7__ {TYPE_1__ mlmeextpriv; } ;
typedef  TYPE_2__ _adapter ;
struct TYPE_8__ {scalar_t__ oper_channel; int /*<<< orphan*/  on_oper_ch_time; } ;

/* Variables and functions */
 TYPE_4__* adapter_to_dvobj (TYPE_2__*) ; 

inline u32 rtw_get_on_cur_ch_time(_adapter *adapter)
{
	if (adapter->mlmeextpriv.cur_channel == adapter_to_dvobj(adapter)->oper_channel)
		return adapter_to_dvobj(adapter)->on_oper_ch_time;
	else
		return 0;
}
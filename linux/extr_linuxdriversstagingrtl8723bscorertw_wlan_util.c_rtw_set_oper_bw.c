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
typedef  int /*<<< orphan*/  u8 ;
struct adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oper_bwmode; } ;

/* Variables and functions */
 TYPE_1__* adapter_to_dvobj (struct adapter*) ; 

inline void rtw_set_oper_bw(struct adapter *adapter, u8 bw)
{
	adapter_to_dvobj(adapter)->oper_bwmode = bw;
}
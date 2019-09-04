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
struct TYPE_2__ {int /*<<< orphan*/  (* c2h_handler ) (struct adapter*,int /*<<< orphan*/ *) ;} ;
struct adapter {TYPE_1__ HalFunc; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  stub1 (struct adapter*,int /*<<< orphan*/ *) ; 

s32 rtw_hal_c2h_handler(struct adapter *adapter, u8 *c2h_evt)
{
	s32 ret = _FAIL;
	if (adapter->HalFunc.c2h_handler)
		ret = adapter->HalFunc.c2h_handler(adapter, c2h_evt);
	return ret;
}
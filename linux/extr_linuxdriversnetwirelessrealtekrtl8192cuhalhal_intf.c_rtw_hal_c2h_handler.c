#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct c2h_evt_hdr {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_5__ {int /*<<< orphan*/  (* c2h_handler ) (TYPE_2__*,struct c2h_evt_hdr*) ;} ;
struct TYPE_6__ {TYPE_1__ HalFunc; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct c2h_evt_hdr*) ; 

s32 rtw_hal_c2h_handler(_adapter *adapter, struct c2h_evt_hdr *c2h_evt)
{
	s32 ret = _FAIL;
	if (adapter->HalFunc.c2h_handler)
		ret = adapter->HalFunc.c2h_handler(adapter, c2h_evt);
	return ret;
}
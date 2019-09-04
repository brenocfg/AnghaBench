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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_bbreg ) (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct adapter {TYPE_1__ HalFunc; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 rtw_hal_read_bbreg(struct adapter *padapter, u32 RegAddr, u32 BitMask)
{
	u32 data = 0;
	if (padapter->HalFunc.read_bbreg)
		 data = padapter->HalFunc.read_bbreg(padapter, RegAddr, BitMask);
	return data;
}
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
typedef  int u32 ;
struct odm_dm_struct {int BoardType; int SupportPlatform; int SupportInterface; } ;
struct adapter {TYPE_1__* HalData; } ;
struct TYPE_2__ {struct odm_dm_struct odmpriv; } ;

/* Variables and functions */

__attribute__((used)) static bool check_condition(struct adapter *adapt, const u32  condition)
{
	struct odm_dm_struct *odm = &adapt->HalData->odmpriv;
	u32 _board = odm->BoardType;
	u32 _platform = odm->SupportPlatform;
	u32 _interface = odm->SupportInterface;
	u32 cond = condition;

	if (condition == 0xCDCDCDCD)
		return true;

	cond = condition & 0x000000FF;
	if ((_board == cond) && cond != 0x00)
		return false;

	cond = condition & 0x0000FF00;
	cond >>= 8;
	if ((_interface & cond) == 0 && cond != 0x07)
		return false;

	cond = condition & 0x00FF0000;
	cond >>= 16;
	if ((_platform & cond) == 0 && cond != 0x0F)
		return false;
	return true;
}
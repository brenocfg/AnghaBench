#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  btChipType; } ;
struct TYPE_4__ {TYPE_1__ boardInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_CHIP_RTL8723B ; 
 TYPE_2__ GLBtCoexist ; 

void EXhalbtcoutsrc_SetChipType(u8 chipType)
{
	GLBtCoexist.boardInfo.btChipType = BTC_CHIP_RTL8723B;
}
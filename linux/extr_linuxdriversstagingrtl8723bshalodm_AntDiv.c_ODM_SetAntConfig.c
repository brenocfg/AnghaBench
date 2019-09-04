#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  Adapter; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_SetBBReg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bMaskDWord ; 

void ODM_SetAntConfig(PDM_ODM_T pDM_Odm, u8 antSetting)// 0=A, 1=B, 2=C, ....
{
	if (antSetting == 0) // ant A
		PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, 0x00000000);
	else if (antSetting == 1)
		PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, 0x00000280);
}
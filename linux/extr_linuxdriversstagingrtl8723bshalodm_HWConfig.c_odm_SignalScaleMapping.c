#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  odm_SignalScaleMapping_92CSeries (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 odm_SignalScaleMapping(PDM_ODM_T pDM_Odm, s32 CurrSig)
{
	return odm_SignalScaleMapping_92CSeries(pDM_Odm, CurrSig);
}
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
typedef  int /*<<< orphan*/  u8 ;
struct hal_com_data {int dummy; } ;
struct adapter {int dummy; } ;
typedef  enum HAL_DEF_VARIABLE { ____Placeholder_HAL_DEF_VARIABLE } HAL_DEF_VARIABLE ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  SetHalDefVar (struct adapter*,int,void*) ; 
 int /*<<< orphan*/  _SUCCESS ; 

u8 SetHalDefVar8723B(struct adapter *padapter, enum HAL_DEF_VARIABLE variable, void *pval)
{
	struct hal_com_data *pHalData;
	u8 bResult;


	pHalData = GET_HAL_DATA(padapter);
	bResult = _SUCCESS;

	switch (variable) {
	default:
		bResult = SetHalDefVar(padapter, variable, pval);
		break;
	}

	return bResult;
}
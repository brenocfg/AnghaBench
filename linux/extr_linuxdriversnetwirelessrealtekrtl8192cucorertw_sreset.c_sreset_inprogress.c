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
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int _FALSE ; 

bool sreset_inprogress(_adapter *padapter)
{
#if defined(DBG_CONFIG_ERROR_RESET)
	HAL_DATA_TYPE	*pHalData = GET_HAL_DATA(padapter);
	return pHalData->srestpriv.silent_reset_inprogress;
#else
	return _FALSE;
#endif
}
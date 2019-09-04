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
struct xmit_frame {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_xmit_c_ ; 
 scalar_t__ rtw_xmit_classifier (int /*<<< orphan*/ *,struct xmit_frame*) ; 

s32 rtw_xmitframe_enqueue(_adapter *padapter, struct xmit_frame *pxmitframe)
{
	if (rtw_xmit_classifier(padapter, pxmitframe) == _FAIL)
	{
		RT_TRACE(_module_rtl871x_xmit_c_, _drv_err_,
			 ("rtw_xmitframe_enqueue: drop xmit pkt for classifier fail\n"));
//		pxmitframe->pkt = NULL;
		return _FAIL;
	}

	return _SUCCESS;
}
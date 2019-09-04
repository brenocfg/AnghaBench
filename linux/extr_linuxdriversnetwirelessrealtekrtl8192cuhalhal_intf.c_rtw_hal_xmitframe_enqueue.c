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
struct xmit_frame {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_5__ {int /*<<< orphan*/  (* hal_xmitframe_enqueue ) (TYPE_2__*,struct xmit_frame*) ;} ;
struct TYPE_6__ {TYPE_1__ HalFunc; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _FALSE ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct xmit_frame*) ; 

s32	rtw_hal_xmitframe_enqueue(_adapter *padapter, struct xmit_frame *pxmitframe)
{
	if(padapter->HalFunc.hal_xmitframe_enqueue)
		return padapter->HalFunc.hal_xmitframe_enqueue(padapter, pxmitframe);

	return _FALSE;	
}
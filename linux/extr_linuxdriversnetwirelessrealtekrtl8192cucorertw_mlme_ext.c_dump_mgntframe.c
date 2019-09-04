#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xmit_frame {int /*<<< orphan*/  pxmitbuf; } ;
struct TYPE_4__ {scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; int /*<<< orphan*/  xmitpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  rtw_free_xmitbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_free_xmitframe (int /*<<< orphan*/ *,struct xmit_frame*) ; 
 int /*<<< orphan*/  rtw_hal_mgnt_xmit (TYPE_1__*,struct xmit_frame*) ; 

void dump_mgntframe(_adapter *padapter, struct xmit_frame *pmgntframe)
{
	if(padapter->bSurpriseRemoved == _TRUE ||
		padapter->bDriverStopped == _TRUE)
	{
		rtw_free_xmitbuf(&padapter->xmitpriv, pmgntframe->pxmitbuf);
		rtw_free_xmitframe(&padapter->xmitpriv, pmgntframe);
		return;
	}

	rtw_hal_mgnt_xmit(padapter, pmgntframe);
}
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
struct xmit_priv {int dummy; } ;
struct TYPE_3__ {scalar_t__ bDriverStopped; scalar_t__ bSurpriseRemoved; scalar_t__ bWritePortCancel; int /*<<< orphan*/  mlmepriv; struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*) ; 
 int _FALSE ; 
 int /*<<< orphan*/  _FW_UNDER_SURVEY ; 
 scalar_t__ _TRUE ; 
 scalar_t__ check_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rtl8192cu_xmitframe_complete (TYPE_1__*,struct xmit_priv*,int /*<<< orphan*/ *) ; 

void rtl8192cu_xmit_tasklet(void *priv)
{	
	int ret = _FALSE;
	_adapter *padapter = (_adapter*)priv;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;

	if(check_fwstate(&padapter->mlmepriv, _FW_UNDER_SURVEY) == _TRUE)
		return;

	while(1)
	{
		if ((padapter->bDriverStopped == _TRUE)||(padapter->bSurpriseRemoved== _TRUE) || (padapter->bWritePortCancel == _TRUE))
		{
			DBG_8192C("xmit_tasklet => bDriverStopped or bSurpriseRemoved or bWritePortCancel\n");
			break;
		}

		ret = rtl8192cu_xmitframe_complete(padapter, pxmitpriv, NULL);

		if(ret==_FALSE)
			break;
		
	}
	
}
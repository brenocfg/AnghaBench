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
typedef  int /*<<< orphan*/  u8 ;
struct xmit_priv {int hwxmit_entry; struct hw_xmit* hwxmits; } ;
struct hw_xmit {int dummy; } ;
struct TYPE_3__ {struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_mfree (int /*<<< orphan*/ *,int) ; 

void rtw_free_hwxmits(_adapter *padapter)
{
	struct hw_xmit *hwxmits;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;

	hwxmits = pxmitpriv->hwxmits;
	if(hwxmits)
		rtw_mfree((u8 *)hwxmits, (sizeof (struct hw_xmit) * pxmitpriv->hwxmit_entry));
}
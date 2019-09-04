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
struct xmit_priv {struct hw_xmit* hwxmits; } ;
struct hw_xmit {int dummy; } ;
struct adapter {struct xmit_priv xmitpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hw_xmit*) ; 

void rtw_free_hwxmits(struct adapter *padapter)
{
	struct hw_xmit *hwxmits;
	struct xmit_priv *pxmitpriv = &padapter->xmitpriv;

	hwxmits = pxmitpriv->hwxmits;
	kfree(hwxmits);
}
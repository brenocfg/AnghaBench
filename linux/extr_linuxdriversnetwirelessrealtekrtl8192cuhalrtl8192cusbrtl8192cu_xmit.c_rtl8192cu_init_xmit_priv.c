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
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_3__ {struct xmit_priv xmitpriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _SUCCESS ; 

s32	rtl8192cu_init_xmit_priv(_adapter *padapter)
{
	struct xmit_priv	*pxmitpriv = &padapter->xmitpriv;

#ifdef PLATFORM_LINUX
	tasklet_init(&pxmitpriv->xmit_tasklet,
	     (void(*)(unsigned long))rtl8192cu_xmit_tasklet,
	     (unsigned long)padapter);
#endif
	return _SUCCESS;
}
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
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  pre_xmitframe (int /*<<< orphan*/ *,struct xmit_frame*) ; 

s32 rtl8192cu_hal_xmit(_adapter *padapter, struct xmit_frame *pxmitframe)
{
	return pre_xmitframe(padapter, pxmitframe);
}
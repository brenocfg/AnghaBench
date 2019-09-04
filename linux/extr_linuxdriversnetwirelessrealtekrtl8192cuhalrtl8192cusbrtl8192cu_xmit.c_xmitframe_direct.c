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
struct xmit_frame {int /*<<< orphan*/  pkt; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  rtw_dump_xframe (int /*<<< orphan*/ *,struct xmit_frame*) ; 
 scalar_t__ rtw_xmitframe_coalesce (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct xmit_frame*) ; 

__attribute__((used)) static s32 xmitframe_direct(_adapter *padapter, struct xmit_frame *pxmitframe)
{
	s32 res = _SUCCESS;


	res = rtw_xmitframe_coalesce(padapter, pxmitframe->pkt, pxmitframe);
	if (res == _SUCCESS) {
		rtw_dump_xframe(padapter, pxmitframe);
	}

	return res;
}
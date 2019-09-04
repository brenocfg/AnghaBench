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
 int /*<<< orphan*/  rtw_dump_xframe (int /*<<< orphan*/ *,struct xmit_frame*) ; 

s32 rtl8192cu_mgnt_xmit(_adapter *padapter, struct xmit_frame *pmgntframe)
{
	return rtw_dump_xframe(padapter, pmgntframe);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct adapter* adapter; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct recv_priv {int /*<<< orphan*/  rx_pkts; } ;
struct adapter {struct recv_priv recvpriv; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 scalar_t__ recv_func (struct adapter*,union recv_frame*) ; 

s32 rtw_recv_entry(union recv_frame *precvframe)
{
	struct adapter *padapter;
	struct recv_priv *precvpriv;
	s32 ret = _SUCCESS;

/* 	RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("+rtw_recv_entry\n")); */

	padapter = precvframe->u.hdr.adapter;

	precvpriv = &padapter->recvpriv;

	ret = recv_func(padapter, precvframe);
	if (ret == _FAIL) {
		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("rtw_recv_entry: recv_func return fail!!!\n"));
		goto _recv_entry_drop;
	}


	precvpriv->rx_pkts++;

	return ret;

_recv_entry_drop:

	/* RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("_recv_entry_drop\n")); */

	return ret;
}
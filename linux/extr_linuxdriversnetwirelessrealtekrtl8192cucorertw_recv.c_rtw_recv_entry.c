#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* adapter; } ;
struct TYPE_6__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct recv_priv {int /*<<< orphan*/  rx_pkts; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_7__ {struct recv_priv recvpriv; } ;
typedef  TYPE_3__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int /*<<< orphan*/  recv_func (TYPE_3__*,union recv_frame*) ; 

s32 rtw_recv_entry(union recv_frame *precvframe)
{
	_adapter *padapter;
	struct recv_priv *precvpriv;
	s32 ret=_SUCCESS;

_func_enter_;

//	RT_TRACE(_module_rtl871x_recv_c_,_drv_info_,("+rtw_recv_entry\n"));

	padapter = precvframe->u.hdr.adapter;

	precvpriv = &padapter->recvpriv;


	if ((ret = recv_func(padapter, precvframe)) == _FAIL)
	{
		RT_TRACE(_module_rtl871x_recv_c_,_drv_info_,("rtw_recv_entry: recv_func return fail!!!\n"));
		goto _recv_entry_drop;
	}


	precvpriv->rx_pkts++;

_func_exit_;

	return ret;

_recv_entry_drop:

#ifdef CONFIG_MP_INCLUDED
	padapter->mppriv.rx_pktloss = precvpriv->rx_drop;
#endif

	//RT_TRACE(_module_rtl871x_recv_c_,_drv_err_,("_recv_entry_drop\n"));

_func_exit_;

	return ret;
}
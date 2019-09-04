#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int dummy; } ;
struct TYPE_6__ {struct rx_pkt_attrib attrib; } ;
struct TYPE_7__ {TYPE_1__ hdr; } ;
union recv_frame {TYPE_2__ u; } ;
struct recv_priv {int /*<<< orphan*/  free_recv_queue; } ;
typedef  int /*<<< orphan*/  _queue ;
struct TYPE_8__ {struct recv_priv recvpriv; } ;
typedef  TYPE_3__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int /*<<< orphan*/  rtw_free_recvframe (union recv_frame*,int /*<<< orphan*/ *) ; 
 int validate_recv_frame (TYPE_3__*,union recv_frame*) ; 

__attribute__((used)) static int recv_func_prehandle(_adapter *padapter, union recv_frame *rframe)
{
	int ret = _SUCCESS;
	struct rx_pkt_attrib *pattrib = &rframe->u.hdr.attrib;
	struct recv_priv *precvpriv = &padapter->recvpriv;
	_queue *pfree_recv_queue = &padapter->recvpriv.free_recv_queue;
	
#ifdef CONFIG_MP_INCLUDED
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
#endif //CONFIG_MP_INCLUDED

#ifdef CONFIG_MP_INCLUDED
	if ((check_fwstate(pmlmepriv, WIFI_MP_STATE) == _TRUE))//&&(padapter->mppriv.check_mp_pkt == 0))
	{
		if (pattrib->crc_err == 1)
			padapter->mppriv.rx_crcerrpktcount++;
		else
			padapter->mppriv.rx_pktcount++;

		if (check_fwstate(pmlmepriv, WIFI_MP_LPBK_STATE) == _FALSE) {
			RT_TRACE(_module_rtl871x_recv_c_, _drv_alert_, ("MP - Not in loopback mode , drop pkt \n"));
			ret = _FAIL;
			rtw_free_recvframe(rframe, pfree_recv_queue);//free this recv_frame
			goto exit;
		}
	}
#endif

	//check the frame crtl field and decache
	ret = validate_recv_frame(padapter, rframe);
	if (ret != _SUCCESS)
	{
		RT_TRACE(_module_rtl871x_recv_c_, _drv_info_, ("recv_func: validate_recv_frame fail! drop pkt\n"));
		rtw_free_recvframe(rframe, pfree_recv_queue);//free this recv_frame
		goto exit;
	}

exit:
	return ret;
}
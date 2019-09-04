#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union recv_frame {int dummy; } recv_frame ;
struct __queue {int dummy; } ;
struct recv_priv {int /*<<< orphan*/  rx_drop; struct __queue free_recv_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  core_rx_post_indicate_err; int /*<<< orphan*/  core_rx_post_portctrl_err; int /*<<< orphan*/  core_rx_post_defrag_err; int /*<<< orphan*/  core_rx_post_decrypt_err; int /*<<< orphan*/  core_rx_post; } ;
struct adapter {TYPE_1__ rx_logs; struct recv_priv recvpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_COUNTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int /*<<< orphan*/  count_rx_stats (struct adapter*,union recv_frame*,int /*<<< orphan*/ *) ; 
 union recv_frame* decryptor (struct adapter*,union recv_frame*) ; 
 union recv_frame* portctrl (struct adapter*,union recv_frame*) ; 
 int process_recv_indicatepkts (struct adapter*,union recv_frame*) ; 
 union recv_frame* recvframe_chk_defrag (struct adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  rtw_free_recvframe (union recv_frame*,struct __queue*) ; 

__attribute__((used)) static int recv_func_posthandle(struct adapter *padapter, union recv_frame *prframe)
{
	int ret = _SUCCESS;
	union recv_frame *orig_prframe = prframe;
	struct recv_priv *precvpriv = &padapter->recvpriv;
	struct __queue *pfree_recv_queue = &padapter->recvpriv.free_recv_queue;

	DBG_COUNTER(padapter->rx_logs.core_rx_post);

	prframe = decryptor(padapter, prframe);
	if (prframe == NULL) {
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("decryptor: drop pkt\n"));
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s decryptor: drop pkt\n", __func__);
		#endif
		ret = _FAIL;
		DBG_COUNTER(padapter->rx_logs.core_rx_post_decrypt_err);
		goto _recv_data_drop;
	}

	prframe = recvframe_chk_defrag(padapter, prframe);
	if (prframe == NULL)	{
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("recvframe_chk_defrag: drop pkt\n"));
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s recvframe_chk_defrag: drop pkt\n", __func__);
		#endif
		DBG_COUNTER(padapter->rx_logs.core_rx_post_defrag_err);
		goto _recv_data_drop;
	}

	prframe = portctrl(padapter, prframe);
	if (prframe == NULL) {
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("portctrl: drop pkt\n"));
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s portctrl: drop pkt\n", __func__);
		#endif
		ret = _FAIL;
		DBG_COUNTER(padapter->rx_logs.core_rx_post_portctrl_err);
		goto _recv_data_drop;
	}

	count_rx_stats(padapter, prframe, NULL);

	ret = process_recv_indicatepkts(padapter, prframe);
	if (ret != _SUCCESS) {
		RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("recv_func: process_recv_indicatepkts fail!\n"));
		#ifdef DBG_RX_DROP_FRAME
		DBG_871X("DBG_RX_DROP_FRAME %s process_recv_indicatepkts fail!\n", __func__);
		#endif
		rtw_free_recvframe(orig_prframe, pfree_recv_queue);/* free this recv_frame */
		DBG_COUNTER(padapter->rx_logs.core_rx_post_indicate_err);
		goto _recv_data_drop;
	}

_recv_data_drop:
	precvpriv->rx_drop++;
	return ret;
}
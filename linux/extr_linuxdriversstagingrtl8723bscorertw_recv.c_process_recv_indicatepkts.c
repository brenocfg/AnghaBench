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
struct ht_priv {int ht_option; } ;
struct mlme_priv {struct ht_priv htpriv; } ;
struct TYPE_2__ {int /*<<< orphan*/  core_rx_post_indicate; } ;
struct adapter {int bDriverStopped; int bSurpriseRemoved; TYPE_1__ rx_logs; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_COUNTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int recv_indicatepkt_reorder (struct adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  rtw_recv_indicatepkt (struct adapter*,union recv_frame*) ; 
 int wlanhdr_to_ethhdr (union recv_frame*) ; 

int process_recv_indicatepkts(struct adapter *padapter, union recv_frame *prframe)
{
	int retval = _SUCCESS;
	/* struct recv_priv *precvpriv = &padapter->recvpriv; */
	/* struct rx_pkt_attrib *pattrib = &prframe->u.hdr.attrib; */
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct ht_priv *phtpriv = &pmlmepriv->htpriv;

	DBG_COUNTER(padapter->rx_logs.core_rx_post_indicate);

	if (phtpriv->ht_option == true) { /* B/G/N Mode */
		/* prframe->u.hdr.preorder_ctrl = &precvpriv->recvreorder_ctrl[pattrib->priority]; */

		if (recv_indicatepkt_reorder(padapter, prframe) != _SUCCESS) { /*  including perform A-MPDU Rx Ordering Buffer Control */
			#ifdef DBG_RX_DROP_FRAME
			DBG_871X("DBG_RX_DROP_FRAME %s recv_indicatepkt_reorder error!\n", __func__);
			#endif

			if ((padapter->bDriverStopped == false) &&
			    (padapter->bSurpriseRemoved == false)) {
				retval = _FAIL;
				return retval;
			}
		}
	} else { /* B/G mode */
		retval = wlanhdr_to_ethhdr(prframe);
		if (retval != _SUCCESS) {
			RT_TRACE(_module_rtl871x_recv_c_, _drv_err_, ("wlanhdr_to_ethhdr: drop pkt\n"));
			#ifdef DBG_RX_DROP_FRAME
			DBG_871X("DBG_RX_DROP_FRAME %s wlanhdr_to_ethhdr error!\n", __func__);
			#endif
			return retval;
		}

		if ((padapter->bDriverStopped == false) && (padapter->bSurpriseRemoved == false)) {
			/* indicate this recv_frame */
			RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("@@@@ process_recv_indicatepkts- recv_func recv_indicatepkt\n"));
			rtw_recv_indicatepkt(padapter, prframe);


		} else{
			RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("@@@@ process_recv_indicatepkts- recv_func free_indicatepkt\n"));

			RT_TRACE(_module_rtl871x_recv_c_, _drv_notice_, ("recv_func:bDriverStopped(%d) OR bSurpriseRemoved(%d)", padapter->bDriverStopped, padapter->bSurpriseRemoved));
			retval = _FAIL;
			return retval;
		}

	}

	return retval;

}
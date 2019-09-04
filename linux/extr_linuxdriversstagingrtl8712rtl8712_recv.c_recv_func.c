#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rx_pkt_attrib {int crc_err; } ;
struct TYPE_6__ {struct rx_pkt_attrib attrib; } ;
struct TYPE_7__ {TYPE_2__ hdr; } ;
union recv_frame {TYPE_3__ u; } ;
struct mlme_priv {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  rx_pktcount; int /*<<< orphan*/  rx_crcerrpktcount; } ;
struct __queue {int dummy; } ;
struct TYPE_5__ {struct __queue free_recv_queue; } ;
struct _adapter {TYPE_4__ mppriv; struct mlme_priv mlmepriv; TYPE_1__ recvpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIFI_MP_LPBK_STATE ; 
 int /*<<< orphan*/  WIFI_MP_STATE ; 
 int _FAIL ; 
 int _SUCCESS ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_phy_info (struct _adapter*,union recv_frame*) ; 
 union recv_frame* r8712_decryptor (struct _adapter*,union recv_frame*) ; 
 int /*<<< orphan*/  r8712_free_recvframe (union recv_frame*,struct __queue*) ; 
 union recv_frame* r8712_portctrl (struct _adapter*,union recv_frame*) ; 
 int r8712_process_recv_indicatepkts (struct _adapter*,union recv_frame*) ; 
 union recv_frame* r8712_recvframe_chk_defrag (struct _adapter*,union recv_frame*) ; 
 int r8712_validate_recv_frame (struct _adapter*,union recv_frame*) ; 

int recv_func(struct _adapter *padapter, void *pcontext)
{
	struct rx_pkt_attrib *pattrib;
	union recv_frame *prframe, *orig_prframe;
	int retval = _SUCCESS;
	struct  __queue *pfree_recv_queue = &padapter->recvpriv.free_recv_queue;
	struct	mlme_priv	*pmlmepriv = &padapter->mlmepriv;

	prframe = pcontext;
	orig_prframe = prframe;
	pattrib = &prframe->u.hdr.attrib;
	if (check_fwstate(pmlmepriv, WIFI_MP_STATE)) {
		if (pattrib->crc_err == 1)
			padapter->mppriv.rx_crcerrpktcount++;
		else
			padapter->mppriv.rx_pktcount++;
		if (!check_fwstate(pmlmepriv, WIFI_MP_LPBK_STATE)) {
			/* free this recv_frame */
			r8712_free_recvframe(orig_prframe, pfree_recv_queue);
			goto _exit_recv_func;
		}
	}
	/* check the frame crtl field and decache */
	retval = r8712_validate_recv_frame(padapter, prframe);
	if (retval != _SUCCESS) {
		/* free this recv_frame */
		r8712_free_recvframe(orig_prframe, pfree_recv_queue);
		goto _exit_recv_func;
	}
	process_phy_info(padapter, prframe);
	prframe = r8712_decryptor(padapter, prframe);
	if (!prframe) {
		retval = _FAIL;
		goto _exit_recv_func;
	}
	prframe = r8712_recvframe_chk_defrag(padapter, prframe);
	if (!prframe)
		goto _exit_recv_func;
	prframe = r8712_portctrl(padapter, prframe);
	if (!prframe) {
		retval = _FAIL;
		goto _exit_recv_func;
	}
	retval = r8712_process_recv_indicatepkts(padapter, prframe);
	if (retval != _SUCCESS) {
		r8712_free_recvframe(orig_prframe, pfree_recv_queue);
		goto _exit_recv_func;
	}
_exit_recv_func:
	return retval;
}
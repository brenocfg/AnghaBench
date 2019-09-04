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
typedef  union recv_frame {int dummy; } recv_frame ;
struct recv_priv {scalar_t__ pallocated_frame_buf; int /*<<< orphan*/ * adapter; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int NR_RECVFRAME ; 
 scalar_t__ RXFRAME_ALIGN_SZ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  rtw_free_uc_swdec_pending_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_hal_free_recv_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_mfree_recv_priv_lock (struct recv_priv*) ; 
 int /*<<< orphan*/  rtw_os_recv_resource_free (struct recv_priv*) ; 
 int /*<<< orphan*/  rtw_vmfree (scalar_t__,scalar_t__) ; 

void _rtw_free_recv_priv (struct recv_priv *precvpriv)
{
	_adapter	*padapter = precvpriv->adapter;

_func_enter_;

	rtw_free_uc_swdec_pending_queue(padapter);

	rtw_mfree_recv_priv_lock(precvpriv);

	rtw_os_recv_resource_free(precvpriv);

	if(precvpriv->pallocated_frame_buf) {
		rtw_vmfree(precvpriv->pallocated_frame_buf, NR_RECVFRAME * sizeof(union recv_frame) + RXFRAME_ALIGN_SZ);
	}

	rtw_hal_free_recv_priv(padapter);

_func_exit_;

}
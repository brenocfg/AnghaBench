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
struct oid_par_priv {int dummy; } ;
typedef  int /*<<< orphan*/  NDIS_STATUS ;

/* Variables and functions */

NDIS_STATUS oid_rt_poll_rx_status_hdl(struct oid_par_priv *poid_par_priv)
{
#if 0
	PADAPTER	Adapter = (PADAPTER)(poid_par_priv->adapter_context);

	NDIS_STATUS	status = NDIS_STATUS_SUCCESS;

_func_enter_;

	if (poid_par_priv->type_of_oid != QUERY_OID)
		return NDIS_STATUS_NOT_ACCEPTED;

	_rtw_memcpy(poid_par_priv->information_buf, (unsigned char*)&Adapter->mppriv.rxstat, sizeof(struct recv_stat));
	*poid_par_priv->bytes_rw = poid_par_priv->information_buf_len;

_func_exit_;

	return status;
#else
	return 0;
#endif
}